#include <audio/mixer/AudioMixer.hpp>
#include <audio/core/AudioBuffer.hpp>
#include <audio/core/AudioControlsChain.hpp>
#include <audio/core/AudioProcess.hpp>
//#include <audio/core/Taps.hpp>
#include <audio/mixer/MixerControlsObserver.hpp>
#include <audio/mixer/AudioMixerBus.hpp>
#include <audio/mixer/AudioMixerStrip.hpp>
#include <audio/mixer/BusControls.hpp>
#include <audio/mixer/Mutation.hpp>
#include <audio/mixer/MixerControls.hpp>
#include <audio/mixer/MixerControlsIds.hpp>
#include <audio/server/AudioServer.hpp>
#include <control/CompoundControl.hpp>
#include <control/Control.hpp>

#include <time.h>
#include <chrono>
#include <thread>

#include <Logger.hpp>

using namespace std;
using namespace ctoot::audio::server;
using namespace ctoot::audio::mixer;

AudioMixer::AudioMixer(weak_ptr<MixerControls> controls, weak_ptr<AudioServer> server)
{
	this->controls = controls;
	this->server = server;
	//Taps::setAudioServer(server);
	sharedAudioBuffer = server.lock()->createAudioBuffer("Mixer (shared)");
	createBusses(controls);
	createStrips(controls);
	observer = make_unique<MixerControlsObserver>(this);
	controls.lock()->addObserver(observer.get());
}

std::weak_ptr<ctoot::audio::server::AudioServer> AudioMixer::getAudioServer() {
	return server;
}

moodycamel::ConcurrentQueue<Mutation*>& AudioMixer::getMutationQueue() {
	return mutationQueue;
}

weak_ptr<MixerControls> AudioMixer::getMixerControls()
{
    return controls;
}

ctoot::audio::core::AudioBuffer* AudioMixer::getSharedBuffer()
{
    return sharedAudioBuffer;
}

ctoot::audio::core::AudioBuffer* AudioMixer::createBuffer(string name)
{
    return server.lock()->createAudioBuffer(name);
}

void AudioMixer::removeBuffer(ctoot::audio::core::AudioBuffer* buffer)
{
    server.lock()->removeAudioBuffer(buffer);
}

bool AudioMixer::isMutating()
{
	return !mutationQueue.size_approx() == 0;
}

void AudioMixer::waitForMutations()
{
	processMutations();
	/* vMPC doesn't need dynamic mutations, only during init.
	while (isMutating()) {
        if(isEnabled() && server->isRunning()) {
			std::this_thread::sleep_for(std::chrono::milliseconds(5));
        } else {
            processMutations();
        }
    }
	if(isEnabled() && server->isRunning()) {
		std::this_thread::sleep_for(std::chrono::milliseconds(20));
	}
	*/
}

weak_ptr<AudioMixerStrip> AudioMixer::getStrip(string name)
{
    waitForMutations();
    return getStripImpl(name);
}

weak_ptr<AudioMixerStrip> AudioMixer::getStripImpl(string name)
{
	for (auto& strip : strips) {
		if (strip->getName().compare(name) == 0) {
			return strip;
		}
	}
	return {};
}

vector<shared_ptr<AudioMixerStrip>> AudioMixer::getStrips()
{
    waitForMutations();
	return strips;
}

weak_ptr<AudioMixerStrip> AudioMixer::getUnusedChannelStrip()
{
	for (auto& strip : channelStrips) {
		if (!strip.lock()->getInputProcess().lock())
			return strip;
	}
	return {};
}

void AudioMixer::work(int nFrames)
{
	if (!enabled) return;
	processMutations();
	silenceStrips(&groupStrips);
	silenceStrips(&fxStrips);
	silenceStrips(&auxStrips);
	mainStrip.lock()->silence();
	evaluateStrips(&channelStrips);
	evaluateStrips(&groupStrips);
	evaluateStrips(&fxStrips);
	evaluateStrips(&auxStrips);
	mainStrip.lock()->processBuffer();
	writeBusBuffers();
}

void AudioMixer::processMutations()
{
	Mutation* m = nullptr;
	mutationQueue.try_dequeue(m);
	if (m == nullptr) return;
	processMutation(m);
}

void AudioMixer::processMutation(Mutation* m)
{
	auto control = dynamic_pointer_cast<core::AudioControlsChain>(m->getControl().lock());
	if (!control) return;
	switch (m->getOperation()) {
	case Mutation::ADD:
		createStrip(control);
		break;
	case Mutation::REMOVE:
		removeStrip(control);
		break;
	}
	delete m;
}

void AudioMixer::evaluateStrips(vector<weak_ptr<AudioMixerStrip>>* strips)
{
	for (auto& strip : (*strips))
		strip.lock()->processBuffer();
}

void AudioMixer::silenceStrips(vector<weak_ptr<AudioMixerStrip>>* strips)
{
	for (auto& strip : (*strips))
		strip.lock()->silence();
}

void AudioMixer::writeBusBuffers()
{
	for (auto& bus : busses)
		bus->write();
}

void AudioMixer::createBusses(weak_ptr<MixerControls> mixerControls)
{
	busses.clear();
	auxBusses.clear();
	fxBusses.clear();
	shared_ptr<AudioMixerBus> bus;

	for (auto& bc : mixerControls.lock()->getAuxBusControls()) {
		bus = createBus(bc);
		busses.push_back(bus);
		auxBusses.push_back(bus);
	}

	for (auto& bc : mixerControls.lock()->getFxBusControls()) {
		bus = createBus(bc);
		busses.push_back(bus);
		fxBusses.push_back(bus);
	}

	mainBus = createBus(mixerControls.lock()->getMainBusControls());
	busses.push_back(mainBus);
}

shared_ptr<AudioMixerBus> AudioMixer::createBus(weak_ptr<BusControls> busControls)
{
	return make_shared<AudioMixerBus>(this, busControls);
}

shared_ptr<AudioMixerBus> AudioMixer::getBus(string name)
{
	for (auto& bus : busses) {
		if (bus->getName().compare(name) == 0) {
			return bus;
		}
	}
	return nullptr;
}

shared_ptr<AudioMixerBus> AudioMixer::getMainBus()
{
    return mainBus;
}

weak_ptr<AudioMixerStrip> AudioMixer::getMainStrip()
{
	if (!mainStrip.lock()) {
		MLOG("getMainStrip() called before mainStrip set");
		return {};
	}
	return mainStrip;
}

void AudioMixer::createStrips(weak_ptr<MixerControls> mixerControls)
{
	for (auto& control : mixerControls.lock()->getControls()) {
		auto candidate = dynamic_pointer_cast<core::AudioControlsChain>(control.lock());
		if (candidate) {
			createStrip(candidate);
		}
	}
}

weak_ptr<AudioMixerStrip> AudioMixer::createStrip(weak_ptr<ctoot::audio::core::AudioControlsChain> controls)
{

	// AudioMixerStrip2 uses a specialised createProcess() method
	//AudioMixerStrip* strip = new AudioMixerStrip2(this, controls);
	auto strip = make_shared<AudioMixerStrip>(this, controls);

	switch (controls.lock()->getId()) {
	case MixerControlsIds::CHANNEL_STRIP:
		channelStrips.push_back(strip);
		break;
	case MixerControlsIds::GROUP_STRIP:
		groupStrips.push_back(strip);
		break;
	case MixerControlsIds::FX_STRIP:
		fxStrips.push_back(strip);
		break;
	case MixerControlsIds::AUX_STRIP:
		auxStrips.push_back(strip);
		break;
	case MixerControlsIds::MAIN_STRIP:
		if (!mainStrip.lock()) {
			mainStrip = strip;
		}
		else {
			MLOG("Only one main strip allowed!");
		}
		break;
	}

	try {
		strips.push_back(strip);
		strip->open();
	} catch (const std::exception& e) {
		string msg = e.what();
		MLOG("Mixer failed to open strip " + strip->getName() + "!");
		MLOG("Error: " + msg);
	}
    return strip;
}

void AudioMixer::removeStrip(weak_ptr<ctoot::audio::core::AudioControlsChain> controls)
{
	for (int i = 0; i < strips.size(); i++) {
		auto strip = strips[i];
		if (strip->getName().compare(controls.lock()->getName()) == 0) {
			strip->close();
			switch (controls.lock()->getId()) {
			case MixerControlsIds::CHANNEL_STRIP:
				for (int j = 0; j < channelStrips.size(); j++) {
					if (channelStrips[j].lock() == strip) {
						channelStrips.erase(channelStrips.begin() + j);
						break;
					}
				}
				break;
			case MixerControlsIds::GROUP_STRIP:
				for (int j = 0; j < groupStrips.size(); j++) {
					if (groupStrips[j].lock() == strip) {
						groupStrips.erase(groupStrips.begin() + j);
						break;
					}
				}
				break;
			case MixerControlsIds::FX_STRIP:
				for (int j = 0; j < fxStrips.size(); j++) {
					if (fxStrips[j].lock() == strip) {
						fxStrips.erase(fxStrips.begin() + j);
						break;
					}
				}
				break;
			case MixerControlsIds::AUX_STRIP:
				for (int j = 0; j < auxStrips.size(); j++) {
					if (auxStrips[j].lock() == strip) {
						auxStrips.erase(auxStrips.begin() + j);
						break;
					}
				}
				break;
			case MixerControlsIds::MAIN_STRIP:
				mainStrip.reset();
				break;
			}
			strips.erase(strips.begin() + i);
			return;
		}
	}
}

void AudioMixer::close()
{
	enabled = false;
    controls.lock()->deleteObserver(observer.get());
	for (auto& s : strips) {
		s->close();
	}
	strips.clear();

	channelStrips.clear();
	groupStrips.clear();
	fxStrips.clear();
	auxStrips.clear();
	
	for (auto& b : busses) {
		b->close();
	}
    busses.clear();
	auxBusses.clear();
	fxBusses.clear();
	server.lock()->removeAudioBuffer(sharedAudioBuffer);
	server.reset();
	//mutationQueue.clear();
	controls.reset();
}

bool AudioMixer::isEnabled()
{
    return enabled;
}

void AudioMixer::setEnabled(bool enabled)
{
    this->enabled = enabled;
}

AudioMixer::~AudioMixer() {
}
