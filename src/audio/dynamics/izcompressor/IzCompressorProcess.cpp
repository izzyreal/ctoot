#include <audio/dynamics/izcompressor/IzCompressorProcess.hpp>

#include <audio/core/AudioBuffer.hpp>
#include <audio/dynamics/izcompressor/IzCompressorProcessVariables.hpp>
#include <dsp/FastMath.hpp>

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

	detectionSamples0 = buffer->getChannel(0);
	detectionSamples1 = buffer->getChannel(1);
	attenuationSamples0 = buffer->getChannel(0);
	attenuationSamples1 = buffer->getChannel(1);

	for (int i = 0; i < buffer->getSampleCount(); i++) {
		(*detectionSamples0)[i] *= inputGain;
		(*detectionSamples1)[i] *= inputGain;
	}

	AudioBuffer* attenuationSpareBuffer = nullptr;

	auto dcm = detectionChannelMode;
	auto acm = attenuationChannelMode;
	bool detIsMidSide = false;

	if (dcm.compare("LR") == 0 && acm.compare("LR") != 0) return AUDIO_OK;

	if (dcm.compare("M") == 0 || dcm.compare("S") == 0) {
		if (!buffer->encodeMidSide()) return AUDIO_OK;
		detIsMidSide = true;
	}

	if (acm.compare("M") == 0 || acm.compare("S") == 0) {
		if (!detIsMidSide) {
			attenuationSpareBuffer = new AudioBuffer("spare", 2, buffer->getSampleCount(), buffer->getSampleRate());
			attenuationSpareBuffer->copyFrom(buffer);
			attenuationSpareBuffer->encodeMidSide();
			attenuationSamples0 = attenuationSpareBuffer->getChannel(0);
			attenuationSamples1 = attenuationSpareBuffer->getChannel(1);
		}
	}

	for (int i = 0; i < len; i++) {

		if (dcm.compare("M") == 0 || dcm.compare("L") == 0) {
			calcGain(detectionSamples0, targetGain, i, mslen, len, sumdiv, gain);
		}
		else if (dcm.compare("S") == 0 || dcm.compare("R") == 0) {
			calcGain(detectionSamples1, targetGain, i, mslen, len, sumdiv, gain);
		}
		else if (dcm.compare("LR") == 0 && acm.compare("LR") == 0) {
			calcGain(detectionSamples0, targetGain, i, mslen, len, sumdiv, gain);
			(*attenuationSamples0)[i] *= gain * makeupGain;
			calcGain(detectionSamples1, targetGain, i, mslen, len, sumdiv, gain);
			(*attenuationSamples1)[i] *= gain * makeupGain;
		}

		if (acm.compare("M") == 0 || acm.compare("L") == 0) {
			(*attenuationSamples0)[i] *= gain * makeupGain;
		}
		else if (acm.compare("S") == 0 || acm.compare("R") == 0) {
			(*attenuationSamples1)[i] *= gain * makeupGain;
		}
		else if (acm.compare("LR") == 0 && dcm.compare("LR") != 0) {
			(*attenuationSamples0)[i] *= gain * makeupGain;
			(*attenuationSamples1)[i] *= gain * makeupGain;
		}
	}
	if (detIsMidSide) buffer->decodeMidSide();
	if (attenuationSpareBuffer != nullptr) {
		buffer->copyFrom(attenuationSpareBuffer);
		buffer->decodeMidSide();
		delete attenuationSpareBuffer;
	}
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
