#include <audio/dynamics/DynamicsProcess.hpp>

#include <audio/core/AudioBuffer.hpp>
#include <audio/dynamics/DynamicsVariables.hpp>
#include <dsp/FastMath.hpp>

#include <cmath>

using namespace ctoot::audio::dynamics;
using namespace std;

void DynamicsProcess::init()
{
	envelope = 0.0f;
	isPeak = false;
	sampleRate = int32_t(0);
	NSQUARESUMS = int32_t(10);
	squaresums = vector<float>(NSQUARESUMS);
	nsqsum = int32_t(0);
	samples = vector<vector<float>*>(6);
	tapSamples = vector<vector<float>*>(6);
}

DynamicsProcess::DynamicsProcess(DynamicsVariables* vars)
	: DynamicsProcess(vars, false)
{
}

DynamicsProcess::DynamicsProcess(DynamicsVariables* vars, bool peak)
{
    init();
    this->vars = vars;
    this->isPeak = peak;
    wasBypassed = !vars->isBypassed();
}

void DynamicsProcess::clear()
{
    envelope = 1.0f;
    vars->setDynamicGain(1.0f);
}

void DynamicsProcess::cacheProcessVariables()
{
    threshold = vars->getThreshold();
    attack = vars->getAttack();
    release = vars->getRelease();
    makeupGain = vars->getGain();
    dryGain = vars->getDryGain();
}

int32_t DynamicsProcess::processAudio(ctoot::audio::core::AudioBuffer* buffer)
{
	auto bypassed = vars->isBypassed();
	if (bypassed) {
		if (!wasBypassed) {
			clear();
		}
		wasBypassed = true;
		return AUDIO_OK;
	}
	wasBypassed = bypassed;
	auto sr = static_cast<int32_t>(buffer->getSampleRate());
	if (sr != sampleRate) {
		sampleRate = sr;
		vars->update(static_cast<float>(sr));
	}
	cacheProcessVariables();
	auto targetGain = 1.0f;
	auto gain = makeupGain;
	auto len = buffer->getSampleCount();
	auto mslen = static_cast<int32_t>((buffer->getSampleRate() / int32_t(1000)));
	auto nc = buffer->getChannelCount();
	for (auto c = int32_t(0); c < nc; c++) {
		samples[c] = &buffer->getChannel(c);
	}
	int32_t nck;
	auto keyBuffer = vars->getKeyBuffer();
	if (keyBuffer == nullptr) {
		keySamples = samples;
		nck = nc;
	}
	else {
		nck = keyBuffer->getChannelCount();
		for (auto c = int32_t(0); c < nck; c++) {
			tapSamples[c] = &keyBuffer->getChannel(c);
		}
		keySamples = tapSamples;
	}
	float sample;
	for (auto i = int32_t(0); i < len; i++) {
		float key = int32_t(0);
		if (isPeak) {
			for (auto c = int32_t(0); c < nck; c++) {
				key = ctoot::dsp::FastMath::max(key, abs((*keySamples[c])[i]));
			}
			targetGain = function(key);
		}
		else if ((i % mslen) == 0) {
			auto length = (i + mslen) > len ? len - i : mslen;
			auto sumOfSquares = 0.0f;
			for (auto c = int32_t(0); c < nck; c++) {
				for (auto j = int32_t(0); j < length; j++) {
					sample = (*keySamples[c])[i + j];
					sumOfSquares += sample * sample;
				}
			}
			squaresums[nsqsum] = sumOfSquares / length;
			float mean = int32_t(0);
			for (auto s = int32_t(0); s < NSQUARESUMS; s++) {
				mean += squaresums[s];
			}
			if (++nsqsum >= NSQUARESUMS)
				nsqsum = 0;

			key = static_cast<float>(sqrt(mean / NSQUARESUMS));
			targetGain = function(key);
		}
		gain = dynamics(targetGain);
		for (auto c = int32_t(0); c < nc; c++) {
			(*samples[c])[i] *= (gain * makeupGain) + dryGain;
		}
	}
	vars->setDynamicGain(gain);
	return AUDIO_OK;
}

float DynamicsProcess::dynamics(float target)
{
    auto factor = target < envelope ? attack : release;
    envelope = factor * (envelope - target) + target;
    return envelope;
}
