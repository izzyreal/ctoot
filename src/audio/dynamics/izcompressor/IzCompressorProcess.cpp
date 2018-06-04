#include <audio/dynamics/izcompressor/IzCompressorProcess.hpp>

#include <audio/core/AudioBuffer.hpp>
#include <audio/dynamics/izcompressor/IzCompressorProcessVariables.hpp>
#include <dsp/FastMath.hpp>

#include <VecUtil.hpp>

using namespace ctoot::audio::dynamics::izcompressor;
using namespace ctoot::audio::dynamics;
using namespace ctoot::dsp;
using namespace ctoot::audio::core;
using namespace std;

#include <Logger.hpp>

IzCompressorProcess::IzCompressorProcess(IzCompressorProcessVariables* vars)
	: IzCompressorProcess(vars, false)
{
}

IzCompressorProcess::IzCompressorProcess(IzCompressorProcessVariables* vars, bool peak)
{
	this->vars = vars;
	this->isPeak = peak;
	wasBypassed = !vars->isBypassed();
	labL = make_unique<moduru::io::CircularTBuffer>(48000);
	labR = make_unique<moduru::io::CircularTBuffer>(48000);
}

void IzCompressorProcess::clear()
{
    envelope = 1.0f;
}

void IzCompressorProcess::cacheProcessVariables()
{
    threshold = vars->getThreshold();
    attack = vars->getAttack();
    release = vars->getRelease();
	lookAhead = vars->getLookAhead();
    makeupGain = vars->getGain();
	detectionChannelMode = vars->getDetectionChannelMode();
	attenuationChannelMode = vars->getAttenuationChannelMode();
	inputGain = vars->getInputGain();
}

int32_t IzCompressorProcess::processAudio(ctoot::audio::core::AudioBuffer* buffer)
{
	auto bypassed = vars->isBypassed();
	if (bypassed) {
		if (!wasBypassed) {
			clear();
		}
		wasBypassed = true;
		return AUDIO_OK;
	}
	auto sr = buffer->getSampleRate();
	if (sr != sampleRate) {
		sampleRate = sr;
		vars->update(sr);
	}
	cacheProcessVariables();
	auto targetGain = 1.0f;
	auto gain = 0.0f;
	auto len = buffer->getSampleCount();
	auto mslen = static_cast<int32_t>(buffer->getSampleRate() * 0.001f);
	auto sumdiv = 1.0f / (mslen + mslen);

	auto b0 = buffer->getChannel(0);
	auto b1 = buffer->getChannel(1);

	if (inputGain != 1.0f) {
		for (int i = 0; i < buffer->getSampleCount(); i++) {
			(*b0)[i] *= inputGain;
			(*b1)[i] *= inputGain;
		}
	}

	auto dcm = detectionChannelMode;
	auto acm = attenuationChannelMode;

	if (dcm.compare("LR") == 0 && acm.compare("LR") != 0) return AUDIO_OK;

	labL->write(b0);
	labR->write(b1);

	vector<float> factorsL(len);
	vector<float> factorsR(len);

	const int lookAheadLenSamples = lookAhead * mslen;

	for (int i = 0; i < len; i++) {
		calcGain(b0, targetGain, i, mslen, len, sumdiv, gain);
		factorsL[i] = (gain * makeupGain);
		calcGain(b1, targetGain, i, mslen, len, sumdiv, gain);
		factorsR[i] = (gain * makeupGain);
	}

	for (int i = 0; i < len; i++) {
		labL->multiply(-lookAheadLenSamples + i, factorsL[i]);
		labR->multiply(-lookAheadLenSamples + i, factorsR[i]);
	}

	labL->moveReadPos(len);
	labR->moveReadPos(len);

	const int correctiveLenSamples = (MAX_LOOK_AHEAD * mslen);

	labL->read(b0, -correctiveLenSamples, len);
	labR->read(b1, -correctiveLenSamples, len);

	vars->setDynamicGain(gain);
	wasBypassed = bypassed;
	return AUDIO_OK;
}

void IzCompressorProcess::calcGain(vector<float>* detectionSamples, float& targetGain, const int sampleIndex, const int mslen, const int len, const float sumdiv, float& gain) {
	float key = 0.0f;
	if (isPeak) {
		key = FastMath::max(key, abs((*detectionSamples)[sampleIndex]));
		targetGain = function(key);
	}
	else if ((sampleIndex % mslen) == 0 && (sampleIndex + mslen) < len) {
		auto sumOfSquares = 0.0f;
		for (int j = 0, k = sampleIndex; j < mslen; j++, k++) {
			sumOfSquares += (*detectionSamples)[k] * (*detectionSamples)[k];
		}
		squaresums[nsqsum] = sumOfSquares * sumdiv;
		float mean = 0.0f;
		for (int s = 0; s < NSQUARESUMS; s++) {
			mean += squaresums[s];
		}
		if (++nsqsum >= NSQUARESUMS)
			nsqsum = 0;

		targetGain = function(sqrt(mean / NSQUARESUMS));
	}
	gain = dynamics(targetGain);
}

float IzCompressorProcess::dynamics(float target)
{
	auto factor = target < envelope ? attack : release;
	envelope = factor * (envelope - target) + target;
	return envelope;
}

IzCompressorProcess::~IzCompressorProcess() {
}
