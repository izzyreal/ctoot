#include <synth/PolyphonicSynthChannel.hpp>

#include <audio/core/MetaInfo.hpp>
#include <audio/core/AudioBuffer.hpp>
#include <audio/core/AudioProcess.hpp>
#include <synth/PolyphonicSynthChannelVoice.hpp>

using namespace ctoot::synth;

PolyphonicSynthChannel::PolyphonicSynthChannel(std::string name)
{
    this->name = name;
}

std::string ctoot::synth::PolyphonicSynthChannel::getName()
{
    return name;
}

void PolyphonicSynthChannel::setLocation(std::string location)
{
    this->location = location;
    info = std::make_shared<ctoot::audio::core::MetaInfo>(name, location);
}

std::string ctoot::synth::PolyphonicSynthChannel::getLocation()
{
    return location;
}

void PolyphonicSynthChannel::open()
{
}

int32_t ctoot::synth::PolyphonicSynthChannel::processAudio(ctoot::audio::core::AudioBuffer* buffer)
{
	buffer->setMetaInfo(info);
	buffer->setChannelFormat(getChannelFormat());
	buffer->makeSilence();
	finished.clear();
	auto sr = static_cast<int32_t>(buffer->getSampleRate());
	auto nactive = int32_t(0);
	//synchronized synchronized_0(voices);
	if (sr != sampleRate) {
		setSampleRate(sr);
		for (auto& voice : voices) {
			voice->setSampleRate(sampleRate);
		}
	}
	for (auto& voice : voices) {
		if (!voice->mix(buffer)) {
			finished.push_back(voice);
		}
		else {
			nactive += 1;
		}
	}
	for (auto voice : finished) {
		for (int i = 0; i < voices.size(); i++) {
			if (voice == voices[i]) {
				voices.erase(voices.begin() + i);
				break;
			}
		}
	}
	return nactive > 0 ? AUDIO_OK : AUDIO_SILENCE;
}

void PolyphonicSynthChannel::close()
{
}

void PolyphonicSynthChannel::setPolyphony(int32_t p)
{
    polyphony = p;
}

int32_t ctoot::synth::PolyphonicSynthChannel::getPolyphony()
{
    return polyphony;
}

void PolyphonicSynthChannel::noteOn(int32_t pitch, int32_t velocity)
{
	auto v = createVoice(pitch, velocity, sampleRate);
	//synchronized synchronized_1(voices);
	if (voices.size() >= polyphony) {
		for (int i = 0; i < voices.size(); i++) {
			if (voices[i]->isReleased()) {
				voices[i]->stop();
				voices.erase(voices.begin() + i);
				break;
			}
		}
	}
	voices.push_back(v);
}

void PolyphonicSynthChannel::noteOff(int32_t pitch)
{
	//synchronized synchronized_2(voices);
	for (auto& voice : voices) {
		if (voice->getPitch() == pitch && !voice->isReleased()) {
			voice->release();
			return;
		}

	}
}

void PolyphonicSynthChannel::allNotesOff()
{
	//synchronized synchronized_3(voices);
	for (auto& voice : voices) {
		voice->release();
	}
}

void PolyphonicSynthChannel::allSoundOff()
{
	//synchronized synchronized_4(voices);
	for (auto& voice : voices) {
		voice->stop();
	}
}

void PolyphonicSynthChannel::noteOff(int32_t pitch, int32_t velocity)
{
    SynthChannel::noteOff(pitch, velocity);
}
