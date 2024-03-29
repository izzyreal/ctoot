#include "InterconnectionOutputProcess.hpp"

#include <audio/core/AudioBuffer.hpp>

#include <audio/mixer/MixerControlsFactory.hpp>

using namespace ctoot::mpc;

InterconnectionOutputProcess::InterconnectionOutputProcess(ctoot::audio::core::AudioBuffer* sharedBuffer)
    : sharedBuffer(sharedBuffer)
{
}

int InterconnectionOutputProcess::processAudio(ctoot::audio::core::AudioBuffer* buffer)
{
    buffer->copyFrom(sharedBuffer);
    return AUDIO_OK;
}

InterconnectionOutputProcess::~InterconnectionOutputProcess() {
}
