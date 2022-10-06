#include <audio/mixer/AudioMixerBus.hpp>
#include <audio/mixer/AudioMixer.hpp>

#include <audio/meter/MeterProcess.hpp>

using namespace ctoot::audio::core;
using namespace ctoot::audio::mixer;
using namespace std;

AudioMixerBus::AudioMixerBus(AudioMixer* mixer, weak_ptr<BusControls> busControls) 
{
	auto lBusControls = busControls.lock();
	this->mixer = mixer;
	name = lBusControls->getName();
	isFx = lBusControls->getId() == MixerControlsIds::FX_BUS;
	channelFormat = lBusControls->getChannelFormat();
	buffer = mixer->createBuffer(name);
	buffer->setChannelFormat(channelFormat);
	setMeterProcess(new ctoot::audio::meter::MeterProcess(busControls.lock()->getMeterControls()));
}

void AudioMixerBus::setOutputProcess(std::weak_ptr<AudioProcess> output)
{
    this->output = output;
}

void AudioMixerBus::setMeterProcess(AudioProcess* meter)
{
    this->meter = meter;
}

AudioBuffer* AudioMixerBus::getBuffer()
{
    return buffer;
}

string AudioMixerBus::getName()
{
    return name;
}

void AudioMixerBus::silence()
{
    buffer->makeSilence();
}

void AudioMixerBus::write(int nFrames)
{
	if (!output.lock() && !isFx) return;

	if (output.lock()) {
		output.lock()->processAudio(buffer, nFrames);
	}
	if (meter != nullptr) {
		meter->processAudio(buffer, nFrames);
	}
}

void AudioMixerBus::close()
{
}

AudioMixerBus::~AudioMixerBus() {
	if (meter != nullptr) {
		delete meter;
	}
}
