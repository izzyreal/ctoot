#include <audio/mixer/AudioMixer.hpp>
#include <audio/core/AudioBuffer.hpp>
#include <audio/core/AudioControlsChain.hpp>
#include <audio/mixer/AudioMixerBus.hpp>
#include <audio/mixer/AudioMixerStrip.hpp>
#include <audio/mixer/BusControls.hpp>
#include <audio/mixer/MixerControls.hpp>
#include <audio/mixer/MixerControlsIds.hpp>
#include <audio/server/AudioServer.hpp>

using namespace std;
using namespace ctoot::audio::server;
using namespace ctoot::audio::mixer;

AudioMixer::AudioMixer(weak_ptr<MixerControls> controls, weak_ptr<AudioServer> server)
{
	this->controls = controls;
	this->server = server;
	sharedAudioBuffer = server.lock()->createAudioBuffer("Mixer (shared)");
	createBusses(controls);
	createStrips(controls);
}

std::weak_ptr<ctoot::audio::server::AudioServer> AudioMixer::getAudioServer() {
	return server;
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

weak_ptr<AudioMixerStrip> AudioMixer::getStrip(string name)
{
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

void AudioMixer::work(int nFrames)
{
	silenceStrips(&groupStrips);
	silenceStrips(&auxStrips);
	mainStrip.lock()->silence();
	evaluateStrips(&channelStrips, nFrames);
	evaluateStrips(&groupStrips, nFrames);
	evaluateStrips(&auxStrips, nFrames);
	mainStrip.lock()->processBuffer(nFrames);
	writeBusBuffers(nFrames);
}

void AudioMixer::evaluateStrips(vector<weak_ptr<AudioMixerStrip>>* strips, int nFrames)
{
	for (auto& strip : (*strips)) {
		strip.lock()->processBuffer(nFrames);
	}
}

void AudioMixer::silenceStrips(vector<weak_ptr<AudioMixerStrip>>* strips)
{
	for (auto& strip : (*strips))
		strip.lock()->silence();
}

void AudioMixer::writeBusBuffers(int nFrames)
{
	for (auto& bus : busses)
		bus->write(nFrames);
}

void AudioMixer::createBusses(weak_ptr<MixerControls> mixerControls)
{
	busses.clear();
	auxBusses.clear();

	shared_ptr<AudioMixerBus> bus;

	for (auto& bc : mixerControls.lock()->getAuxBusControls()) {
		bus = createBus(bc);
		busses.push_back(bus);
		auxBusses.push_back(bus);
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

	auto strip = make_shared<AudioMixerStrip>(this, controls);

	switch (controls.lock()->getId()) {
	case MixerControlsIds::CHANNEL_STRIP:
		channelStrips.push_back(strip);
		break;
	case MixerControlsIds::GROUP_STRIP:
		groupStrips.push_back(strip);
		break;
	case MixerControlsIds::AUX_STRIP:
		auxStrips.push_back(strip);
		break;
	case MixerControlsIds::MAIN_STRIP:
		if (!mainStrip.lock()) {
			mainStrip = strip;
		}
		break;
	}

	try {
		strips.push_back(strip);
		strip->open();
	} catch (const std::exception&) {
	}

    return strip;
}

void AudioMixer::close()
{
	for (auto& s : strips) {
		s->close();
	}
	strips.clear();

	channelStrips.clear();
	groupStrips.clear();
	auxStrips.clear();

	for (auto& b : busses) {
		b->close();
	}
    busses.clear();
	auxBusses.clear();
	server.lock()->removeAudioBuffer(sharedAudioBuffer);
	server.reset();
	controls.reset();
}
