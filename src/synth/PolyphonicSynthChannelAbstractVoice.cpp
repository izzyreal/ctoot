#include <synth/PolyphonicSynthChannelAbstractVoice.hpp>

#include <audio/core/AudioBuffer.hpp>
#include <synth/PolyphonicSynthChannel.hpp>
#include <synth/SynthChannel.hpp>

using namespace ctoot::synth;

PolyphonicSynthChannelAbstractVoice::PolyphonicSynthChannelAbstractVoice(int32_t pitch, int32_t velocity)
{
    this->pitch = pitch;
    this->velocity = velocity;
    amplitude = static_cast< float >(velocity) / int32_t(128);
    frequency = SynthChannel::midiFreq(pitch);
}

int32_t ctoot::synth::PolyphonicSynthChannelAbstractVoice::getPitch()
{
    return pitch;
}

void PolyphonicSynthChannelAbstractVoice::release()
{
    release_ = true;
}

bool ctoot::synth::PolyphonicSynthChannelAbstractVoice::isReleased()
{
    return release_;
}

void PolyphonicSynthChannelAbstractVoice::stop()
{
    stop_ = true;
}

bool ctoot::synth::PolyphonicSynthChannelAbstractVoice::mix(ctoot::audio::core::AudioBuffer* buffer)
{
    if(stop_)
        return false;

    auto samples = buffer->getChannel(0);
    auto nsamples = buffer->getSampleCount();
    for (auto i = int32_t(0); i < nsamples; i++) {
        (*samples)[i] += getSample();
    }
    return !isComplete();
}
