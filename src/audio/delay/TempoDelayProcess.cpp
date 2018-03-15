#include <audio/delay/TempoDelayProcess.hpp>

#include <audio/core/AudioBuffer.hpp>
#include <audio/delay/DelayBuffer.hpp>
#include <audio/delay/TempoDelayProcess1.hpp>
#include <audio/delay/TempoDelayProcessVariables.hpp>

#include <Logger.hpp>

using namespace ctoot::audio::delay;
using namespace std;

TempoDelayProcess::TempoDelayProcess(TempoDelayProcessVariables* vars)
{
	bpm = 120.0f;
	meansquare = 0.0f;
	meanK = 0.2f;
	this->vars = vars;
	wasBypassed = !vars->isBypassed();
	//tempoListener = new TempoDelayProcess1(this);
	smoothedMix = vars->getMix();
}

void TempoDelayProcess::open()
{
	//::uk::org::toot::misc::Tempo::addTempoListener(tempoListener);
}

int TempoDelayProcess::processAudio(ctoot::audio::core::AudioBuffer* buffer)
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
	auto sampleRate = buffer->getSampleRate();
	auto ns = buffer->getSampleCount();
	auto nc = buffer->getChannelCount();
	auto feedback = vars->getFeedback();
	feedback = 0.75;
	auto mix = vars->getMix();
	if (delayBuffer == nullptr) {
		delayBuffer = new DelayBuffer(nc, msToSamples(vars->getMaxDelayMilliseconds(), sampleRate), sampleRate);
		MLOG("max delay ms: " + to_string(vars->getMaxDelayMilliseconds()));
		MLOG("delay buffer size: " + to_string(delayBuffer->getSampleCount()));
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
	auto ducking = vars->getDucking();
	if (ducking < 1.0f) {
		auto square = buffer->square();
		meansquare += meanK * (square - meansquare);
		auto rms = 10.0f * sqrt(meansquare);
		if (rms < ducking) {
		}
		else if (rms > 1.0f) {
			mix *= ducking;
		}
		else {
			mix *= ducking / rms;
		}
	}
	smoothedMix += 0.05f * (mix - smoothedMix);
	tappedBuffer->makeSilence();
	auto delay = static_cast<int>(msToSamples(60000.0 * vars->getDelayFactor() / bpm, sampleRate));
	//MLOG("delay: " + to_string(delay));
	for (int c = 0; c < nc; c++) {
		if (delay < ns)
			continue;

		delayBuffer->tap(c, tappedBuffer, delay, 1.0f);
	}
	delayBuffer->appendFiltered(buffer, tappedBuffer, feedback * 1.1f, vars->getLowpassCoefficient());
	for (int c = 0; c < nc; c++) {
		auto samples = buffer->getChannel(c);
		auto tapped = tappedBuffer->getChannel(c);
		for (int i = 0; i < ns; i++) {
			//(*samples)[i] += smoothedMix * (*tapped)[i];
			(*samples)[i] = smoothedMix * (*tapped)[i];
		}
	}
	wasBypassed = bypassed;
	return AUDIO_OK;
}

void TempoDelayProcess::close()
{
	if (delayBuffer != nullptr)
		delete delayBuffer;
	if (tappedBuffer != nullptr)
		delete tappedBuffer;
	//::uk::org::toot::misc::Tempo::removeTempoListener(tempoListener);
}

int TempoDelayProcess::msToSamples(float ms, float sr)
{
	return static_cast< int >(((ms * sr) / 1000.0));
}
