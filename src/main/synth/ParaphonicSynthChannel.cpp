#include <synth/ParaphonicSynthChannel.hpp>

using namespace ctoot::synth;

ParaphonicSynthChannel::ParaphonicSynthChannel(std::string name)
	: PolyphonicSynthChannel(name)
{
}

int32_t ctoot::synth::ParaphonicSynthChannel::processAudio(ctoot::audio::core::AudioBuffer* buffer)
{
    auto ret = PolyphonicSynthChannel::processAudio(buffer);
    postProcessAudio(buffer, ret);
    return ret;
}

void ParaphonicSynthChannel::close()
{
    PolyphonicSynthChannel::close();
}

void ParaphonicSynthChannel::open()
{
    PolyphonicSynthChannel::open();
}

std::string ctoot::synth::ParaphonicSynthChannel::getLocation()
{
    return PolyphonicSynthChannel::getLocation();
}

std::string ctoot::synth::ParaphonicSynthChannel::getName()
{
    return PolyphonicSynthChannel::getName();
}
