#include <audio/delay/ModulatedDelayProcess.hpp>

#include <audio/core/AudioBuffer.hpp>
#include <audio/core/ChannelFormat.hpp>
#include <audio/core/FloatDenormals.hpp>
#include <audio/delay/DelayBuffer.hpp>
#include <audio/delay/ModulatedDelayProcessVariables.hpp>

#define _USE_MATH_DEFINES
#include <math.h>  

using namespace ctoot::audio::delay;
using namespace std;

ModulatedDelayProcess::ModulatedDelayProcess(ModulatedDelayProcessVariables* vars)
{
	phaseQuad = false;
	samples = vector<vector<float>*>(6);
	this->vars = vars;
	modulatorMap = vector<int>(8);
    wasBypassed = !vars->isBypassed();
}

void ModulatedDelayProcess::open()
{
}

int ModulatedDelayProcess::processAudio(ctoot::audio::core::AudioBuffer* buffer)
{
	auto bypassed = vars->isBypassed();
	if (bypassed) {
		if (!wasBypassed) {
			if (delayBuffer != nullptr)
				delayBuffer->makeSilence();

			wasBypassed = true;
		}
		return AUDIO_OK;
	}
	wasBypassed = bypassed;
	phaseQuad = vars->isPhaseQuadrature();
	if (phaseQuad)
		buffer->monoToStereo();

	auto sampleRate = buffer->getSampleRate();
	if (delayBuffer == nullptr) {
		delayBuffer = new DelayBuffer(buffer->getChannelCount(), msToSamples(vars->getMaxDelayMilliseconds(), sampleRate), sampleRate);
	}
	auto ns = buffer->getSampleCount();
	auto nc = buffer->getChannelCount();
	auto depth = vars->getDepth();
	auto feedback = vars->getFeedback();
	auto dry = vars->getDry();
	auto wet = vars->getWet();
	auto staticDelay = static_cast<int>((delayBuffer->msToSamples(vars->getDelayMilliseconds())));
	delayBuffer->conform(buffer);
	auto f = buffer->getChannelFormat();
	if (format.lock() != f.lock()) {
		format = f.lock();
		buildModulatorMap(buffer);
	}
	auto timeDelta = float(1) / sampleRate;
	auto depth2 = staticDelay * depth;
	for (int c = 0; c < nc; c++) {
		samples[c] = buffer->getChannel(c);
	}
	for (int s = 0; s < ns; s++) {
		incrementModulators(timeDelta);
		for (auto ch = int(0); ch < nc; ch++) {
			auto in = (*samples[ch])[s];
			delayBuffer->append(ch, ctoot::audio::core::FloatDenormals::zeroDenorm(in - feedback * delayBuffer->outU(ch, staticDelay)));
			(*samples[ch])[s] = dry * in + wet * delayBuffer->outA(ch, staticDelay + modulation(ch) * depth2);
		}
		delayBuffer->nudge(1);
	}
	return AUDIO_OK;
}

void ModulatedDelayProcess::close()
{
	if (delayBuffer != nullptr)
		delete delayBuffer;
}

void ModulatedDelayProcess::buildModulatorMap(ctoot::audio::core::AudioBuffer* buffer)
{
	auto nc = buffer->getChannelCount();
	for (auto ch = int(0); ch < nc; ch++) {
		if (format.lock()->isLFE(ch))
			modulatorMap[ch] = -1;
		else if (!phaseQuad) {
			modulatorMap[ch] = 0;
		}
		else {
			if (format.lock()->isLeft(ch))
				modulatorMap[ch] = 0;
			else if (format.lock()->isRight(ch))
				modulatorMap[ch] = 1;
			else
				modulatorMap[ch] = -1;
		}
	}
}

void ModulatedDelayProcess::incrementModulators(float timeDelta)
{
	auto phaseDelta = timeDelta * vars->getRate() * int(2)* M_PI;
	modulatorPhase += phaseDelta;
	if (modulatorPhase > M_PI) {
		modulatorPhase -= int(2) * M_PI;
	}
	if (!phaseQuad)
		return;

	modulatorPhaseQuad = modulatorPhase + 0.5f * static_cast<float>(M_PI);
	if (modulatorPhaseQuad > M_PI) {
		modulatorPhaseQuad -= int(2) * M_PI;
	}
}

#define TWODIVPI (float)(2 / M_PI);

static inline float triangle(float x) {
	x += M_PI;
	x *= TWODIVPI;
	x -= 1;
	if (x > 1) x -= 4.0f;
	return abs(-(abs(x) - 2)) - 1;
}

float ModulatedDelayProcess::modulation(int chan)
{
	if (modulatorMap[chan] < 0)
		return 0.0f;

	auto phase = modulatorMap[chan] == 0 ? modulatorPhase : modulatorPhaseQuad;
	auto shape = vars->getLFOShape();
	auto mod = (shape == 0) ? sin(phase) : triangle(phase);
	if (mod < -1.0f)
		mod = -1.0f;
	else if (mod > 1.0f)
		mod = 1.0f;

	return mod;
}

int ModulatedDelayProcess::msToSamples(float ms, float sr)
{
	return round((ms * sr) / int(1000));
}
