#include "IzCompressorProcess.hpp"

#include <audio/core/AudioBuffer.hpp>
#include "IzCompressorProcessVariables.hpp"
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
	lab = make_unique<moduru::io::StereoCircularTBuffer>(48000);
	dryBuffer = make_unique<moduru::io::StereoCircularTBuffer>(48000);
}

void IzCompressorProcess::clear()
{
    envelope = 1.0f;
}

void IzCompressorProcess::cacheProcessVariables()
{
	auto cl = vars->getLink().lock();
    threshold = cl ? cl->getThreshold() : vars->getThreshold();
    attack = vars->getAttack();
    release = cl ? cl->getThreshold() : vars->getRelease();
	lookAhead = vars->getLookAhead();
    makeupGain = vars->getGain();
	detectionChannelMode = vars->getDetectionChannelMode();
	attenuationChannelMode = vars->getAttenuationChannelMode();
	inputGain = vars->getInputGain();
	outputGain = vars->getOutputGain();
	mute = vars->getMute();
	dryGain = vars->getDryGain();
	wetGain = vars->getWetGain();
}

int32_t IzCompressorProcess::processAudio(ctoot::audio::core::AudioBuffer* buffer)
{
	auto key = vars->getKeyBuffer();
	if (key == nullptr) {
		//MLOG("processAudio key == nullptr!");
	}
	else {
		//MLOG("processAudio key is fine :)");
		int counter = 0;
		for (auto& f : *key->getChannel(0)) {
			//MLOG(to_string(f));
			if (counter++ > 100) break;
		}
	}
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

	//auto dBuffer0 = buffer->getChannel(0);
	//auto dBuffer1 = buffer->getChannel(1);

	auto dBuffer0 = key != nullptr ? key->getChannel(0) : buffer->getChannel(0);
	auto dBuffer1 = key != nullptr ? key->getChannel(1) : buffer->getChannel(1);

	auto aBuffer0 = buffer->getChannel(0);
	auto aBuffer1 = buffer->getChannel(1);

	dryBuffer->write(aBuffer0, aBuffer1);

	smoothedInputGain += 0.05f * (inputGain - smoothedInputGain);

	for (int i = 0; i < buffer->getSampleCount(); i++) {
		(*dBuffer0)[i] *= smoothedInputGain;
		(*dBuffer1)[i] *= smoothedInputGain;
	}

	auto dcm = detectionChannelMode;
	auto acm = attenuationChannelMode;

	//if (dcm.compare("LR") == 0 && acm.compare("LR") != 0) return AUDIO_OK;

	lab->write(aBuffer0, aBuffer1);

	if (mute) {
		//MLOG("band is muted");
		buffer->makeSilence();
		lab->moveReadPos(len);
		dryBuffer->moveReadPos(len);
		vars->setDynamicGain(1.0f);
		return AUDIO_OK;
	}
	else {
		//MLOG("band is not muted");
	}

	vector<float> factorsL(len);
	vector<float> factorsR(len);

	const int lookAheadLenSamples = lookAhead * mslen;

	if (dcm.compare("M") == 0 || dcm.compare("S") == 0) {
		buffer->encodeMidSide();
	}

	bool dcmM = dcm.compare("M") == 0;
	bool dcmS = dcm.compare("S") == 0;
	bool dcmL = dcm.compare("L") == 0;
	bool dcmR = dcm.compare("R") == 0;
	bool dcmLR = dcm.compare("LR") == 0;
	bool acmM = acm.compare("M") == 0;
	bool acmS = acm.compare("S") == 0;
	bool acmL = acm.compare("L") == 0;
	bool acmR = acm.compare("R") == 0;
	bool acmLR = acm.compare("LR") == 0;

	for (int i = 0; i < len; i++) {
		if (dcmM || dcmL || dcmLR) {
			calcGain(dBuffer0, targetGain, i, mslen, len, sumdiv, gain);
			factorsL[i] = (gain * makeupGain);
		}
		if (dcmS || dcmR || dcmLR) {
			calcGain(dBuffer1, targetGain, i, mslen, len, sumdiv, gain);
			factorsR[i] = (gain * makeupGain);
		}
	}

	float factorL;
	float factorR;
	for (int i = 0; i < len; i++) {
		if (acmM) {
			float factor = factorsL[i];
			if (dcmS || dcmR) factor = factorsR[i];
			lab->encodeMidSide(-lookAheadLenSamples + i);
			lab->multiply(-lookAheadLenSamples + i, factor, true);
			lab->decodeMidSide(-lookAheadLenSamples + i);
		}
		else if (acmS) {
			float factor = factorsR[i];
			if (dcmM || dcmL) factor = factorsL[i];
			lab->encodeMidSide(-lookAheadLenSamples + i);
			lab->multiply(-lookAheadLenSamples + i, factor, false);
			lab->decodeMidSide(-lookAheadLenSamples + i);
		}
		else if (acmL) {
			float factor = factorsL[i];
			if (dcmS || dcmR) factor = factorsR[i];
			lab->multiply(-lookAheadLenSamples + i, factor, true);
		}
		else if (acmR) {
			float factor = factorsR[i];
			if (dcmM || dcmL) factor = factorsL[i];
			lab->multiply(-lookAheadLenSamples + i, factor, false);
		}
		else if (acmLR) {
			factorL = factorsL[i];
			factorR = factorsR[i];
			if (dcmL || dcmM)
				factorR = factorL;
			if (dcmR || dcmS)
				factorL = factorR;
			lab->multiply(-lookAheadLenSamples + i, factorL, true);
			lab->multiply(-lookAheadLenSamples + i, factorR, false);
		}
	}

	const int correctiveLenSamples = (MAX_LOOK_AHEAD * mslen);

	lab->read(aBuffer0, aBuffer1, -correctiveLenSamples, len);
	lab->moveReadPos(len);
	
	vector<float> dryL(len);
	vector<float> dryR(len);

	dryBuffer->read(&dryL, &dryR, -correctiveLenSamples, len);
	dryBuffer->moveReadPos(len);

	smoothedWetGain += 0.05f * (wetGain - smoothedWetGain);
	smoothedDryGain += 0.05f * (dryGain - smoothedDryGain);

	for (int i = 0; i < len; i++) {
		(*aBuffer0)[i] = ((*aBuffer0)[i] * smoothedWetGain) + (dryL[i] * smoothedDryGain);
		(*aBuffer0)[i] *= outputGain;
		(*aBuffer1)[i] = ((*aBuffer1)[i] * smoothedWetGain) + (dryR[i] * smoothedDryGain);
		(*aBuffer1)[i] *= outputGain;
	}
	vars->setDynamicGain(gain >= 0.999937f ? 1.0f : gain);
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
