#include "CabMicingProcess.hpp"

#include <audio/core/ChannelFormat.hpp>
#include <audio/delay/DelayBuffer.hpp>
#include <audio/delay/DelayTap.hpp>

using namespace ctoot::audio::delay;
using namespace ctoot::audio::core;
using namespace std;

CabMicingProcess::CabMicingProcess(CabMicingProcess_Variables* vars)
{
    this->vars = vars;
    wasBypassed = !vars->isBypassed();
}

void ctoot::audio::delay::CabMicingProcess::open()
{
}

int ctoot::audio::delay::CabMicingProcess::processAudio(AudioBuffer* buffer)
{
	auto bypassed = vars->isBypassed();
	if (bypassed) {
		if (!wasBypassed) {
			if (delayBuffer != nullptr) {
				delayBuffer->makeSilence();
			}
			wasBypassed = true;
		}
		return AUDIO_OK;
	}
	wasBypassed = bypassed;
	buffer->convertTo(ChannelFormat::MONO());
	auto sampleRate = buffer->getSampleRate();
	auto samplesPerMilli = sampleRate * 0.001f;
	if (delayBuffer == nullptr) {
		delayBuffer = new DelayBuffer(1, static_cast<int>((30 * samplesPerMilli)), sampleRate);
	}
	else {
		delayBuffer->conform(buffer);
	}
	delayBuffer->append(buffer);
	for (auto& tap : vars->getTaps()) {
		{
			auto level = tap->getLevel();
			if (level < 0.001)
				continue;

			auto delay = static_cast<int>(tap->getDelayMilliseconds() * samplesPerMilli);
			delayBuffer->tap(0, buffer, delay, level);
		}
	}
	return AUDIO_OK;
}

void ctoot::audio::delay::CabMicingProcess::close()
{
	delete delayBuffer;
}
