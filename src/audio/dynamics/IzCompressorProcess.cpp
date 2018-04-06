#include <audio/dynamics/IzCompressorProcess.hpp>

#include <audio/core/AudioBuffer.hpp>
#include <audio/dynamics/IzCompressorProcessVariables.hpp>
#include <dsp/FastMath.hpp>

using namespace ctoot::audio::dynamics;
using namespace ctoot::dsp;
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
    makeupGain = vars->getGain();
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

	//if (!buffer->encodeMidSide())
		//return AUDIO_OK;

	detectionSamplesL = buffer->getChannel(0);
	detectionSamplesR = buffer->getChannel(1);
	attenuationSamplesL = buffer->getChannel(0);
	attenuationSamplesR = buffer->getChannel(1);

	for (int i = 0; i < len; i++) {
		auto detSample = (*detectionSamplesL)[i];
		calcGain(detSample, targetGain, i, mslen, len, sumdiv, gain);
		(*attenuationSamplesL)[i] *= gain * makeupGain;
		(*attenuationSamplesR)[i] *= gain * makeupGain;
	}

	//buffer->decodeMidSide();
	vars->setDynamicGain(gain);
	wasBypassed = bypassed;
	return AUDIO_OK;
}

void IzCompressorProcess::calcGain(const float detection, float& targetGain, const int sampleIndex, const int mslen, const int len, const float sumdiv, float& gain) {
	float key = 0.0f;
	if (isPeak) {
		key = FastMath::max(key, abs(detection));
		targetGain = function(key);
	}
	else if ((sampleIndex % mslen) == 0 && (sampleIndex + mslen) < len) {
		auto sumOfSquares = 0.0f;
		for (int j = 0, k = sampleIndex; j < mslen; j++, k++) {
			sumOfSquares += (*detectionSamplesL)[k] * (*detectionSamplesL)[k];
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
