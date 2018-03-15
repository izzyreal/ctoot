#include <audio/delay/MultiTapDelayProcess.hpp>

#include <audio/core/AudioBuffer.hpp>
#include <audio/core/ChannelFormat.hpp>
#include <audio/delay/DelayBuffer.hpp>
#include <audio/delay/DelayTap.hpp>
#include <audio/delay/MultiTapDelayProcessVariables.hpp>

using namespace ctoot::audio::delay;

MultiTapDelayProcess::MultiTapDelayProcess(MultiTapDelayProcessVariables* vars)
{
    this->vars = vars;
    wasBypassed = !vars->isBypassed();
}

void MultiTapDelayProcess::open()
{
}

int MultiTapDelayProcess::processAudio(ctoot::audio::core::AudioBuffer* buffer)
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
	buffer->monoToStereo();
	auto sampleRate = buffer->getSampleRate();
	auto samplesPerMilli = sampleRate * 0.001f;
	auto ns = buffer->getSampleCount();
	auto nc = buffer->getChannelCount();
	auto feedback = vars->getFeedback();
	auto mix = vars->getMix();
	if (delayBuffer == nullptr) {
		delayBuffer = new DelayBuffer(nc, static_cast<int>((vars->getMaxDelayMilliseconds() * samplesPerMilli)), sampleRate);
	}
	else {
		delayBuffer->conform(buffer);
	}
	if (tappedBuffer == nullptr) {
		tappedBuffer = new DelayBuffer(nc, ns, sampleRate);
	}
	else {
		tappedBuffer->conform(buffer);
		if (tappedBuffer->getSampleCount() != ns) {
			tappedBuffer->changeSampleCount(ns, false);
		}
	}
	tappedBuffer->makeSilence();
	auto delayFactor = vars->getDelayFactor();
	auto format = buffer->getChannelFormat();
	for (auto c = int(0); c < nc; c++) {
		int c2;
		if (format.lock()->isLeft(c))
			c2 = ctoot::audio::core::ChannelFormat::STEREO().lock()->getLeft()[int(0)];
		else if (format.lock()->isRight(c))
			c2 = ctoot::audio::core::ChannelFormat::STEREO().lock()->getRight()[int(0)];
		else
			continue;
		for (auto& tap : vars->getTaps(c2)) {
			auto level = tap.lock()->getLevel();
			if (level < 0.001)
				continue;

			auto delay = static_cast<int>((tap.lock()->getDelayMilliseconds() * delayFactor * samplesPerMilli));
			if (delay < ns)
				continue;

			delayBuffer->tap(c, tappedBuffer, delay, level);
		}
	}
	delayBuffer->append(buffer, tappedBuffer, feedback);
	for (int c = 0; c < nc; c++) {
		auto samples = buffer->getChannel(c);
		auto tapped = tappedBuffer->getChannel(c);
		for (auto i = int(0); i < ns; i++) {
			(*samples)[i] += mix * (*tapped)[i];
		}
	}
	wasBypassed = bypassed;
	return AUDIO_OK;
}

void MultiTapDelayProcess::close()
{
	if (delayBuffer != nullptr)
		delete delayBuffer;
	if (tappedBuffer != nullptr)
		delete tappedBuffer;
}
