#include <synth/MonophonicSynthChannel.hpp>

#include <audio/core/MetaInfo.hpp>
#include <audio/core/AudioBuffer.hpp>
#include <audio/core/AudioProcess.hpp>

using namespace ctoot::synth;

MonophonicSynthChannel::MonophonicSynthChannel(std::string name)
{
    this->name = name;
}

std::string ctoot::synth::MonophonicSynthChannel::getName()
{
    return name;
}

void MonophonicSynthChannel::setLocation(std::string location)
{
    this->location = location;
	info = std::make_shared<ctoot::audio::core::MetaInfo>(name, location);
}

std::string ctoot::synth::MonophonicSynthChannel::getLocation()
{
    return location;
}

void MonophonicSynthChannel::noteOn(int32_t pitch, int32_t velocity)
{
	noteCount += 1;
	targetFrequency = midiFreq(pitch);
	targetSemitones = pitch;
	amplitude = velocity / 128.0f;
	if (noteCount == 1 || !isGlideEnabled()) {
		frequency = targetFrequency;
		semitones = targetSemitones;
		trigger(amplitude);
	}
	else {
		auto nblocks = getGlideMilliseconds() * sampleRate / int32_t(1000) / sampleCount;
		glideFactor = static_cast<float>(pow(targetFrequency / frequency, 1.0 / nblocks));
		semitoneIncrement = (targetSemitones - semitones) / nblocks;
		gliding = true;
	}
}

void MonophonicSynthChannel::noteOff(int32_t pitch)
{
	noteCount -= 1;
	if (noteCount == 0) {
		release();
	}
}

void MonophonicSynthChannel::open()
{
}

int32_t ctoot::synth::MonophonicSynthChannel::processAudio(ctoot::audio::core::AudioBuffer* buffer)
{
	buffer->setMetaInfo(info);
	buffer->setChannelFormat(getChannelFormat());
	if (isComplete()) {
		buffer->makeSilence();
		return AUDIO_SILENCE;
	}
	sampleCount = buffer->getSampleCount();
	auto sr = static_cast<int32_t>(buffer->getSampleRate());
	if (sr != sampleRate) {
		setSampleRate(sr);
		sampleRate = sr;
	}
	if (gliding)
		glide();

	update(frequency);
	auto samples = buffer->getChannel(0);
	auto nsamples = buffer->getSampleCount();
	for (auto i = int32_t(0); i < nsamples; i++) {
		(*samples)[i] += getSample();
	}
	return AUDIO_OK;
}

void MonophonicSynthChannel::close()
{
}

void MonophonicSynthChannel::glide()
{
	semitones += semitoneIncrement;
	frequency *= glideFactor;
	if (glideFactor < 1.0f) {
		if (frequency <= targetFrequency) {
			frequency = targetFrequency;
			semitones = targetSemitones;
			gliding = false;
		}
	}
	else {
		if (frequency >= targetFrequency) {
			frequency = targetFrequency;
			semitones = targetSemitones;
			gliding = false;
		}
	}
}

void MonophonicSynthChannel::allNotesOff()
{
    release();
    noteCount = 0;
}

void MonophonicSynthChannel::allSoundOff()
{
}

void MonophonicSynthChannel::noteOff(int32_t pitch, int32_t velocity)
{
    SynthChannel::noteOff(pitch, velocity);
}
