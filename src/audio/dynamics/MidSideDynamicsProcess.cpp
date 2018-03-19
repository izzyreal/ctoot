#include <audio/dynamics/MidSideDynamicsProcess.hpp>

#include <audio/core/AudioBuffer.hpp>
#include <audio/dynamics/MidSideDynamicsProcessVariables.hpp>
#include <dsp/FastMath.hpp>

using namespace ctoot::audio::dynamics;
using namespace std;

void MidSideDynamicsProcess::init()
{
	envelope = vector<float>(2);
    isPeak = false;
	sampleRate = 0;
	NSQUARESUMS = 10;
    squaresumsM = vector<float>(NSQUARESUMS);
    squaresumsS = vector<float>(NSQUARESUMS);
	nsqsum = 0;
}

MidSideDynamicsProcess::MidSideDynamicsProcess(MidSideDynamicsProcessVariables* vars)
	: MidSideDynamicsProcess(vars, false)
{
}

MidSideDynamicsProcess::MidSideDynamicsProcess(MidSideDynamicsProcessVariables* vars, bool peak)
{
	init();
	this->vars = vars;
	this->isPeak = peak;
	wasBypassed = !vars->isBypassed();
}

void MidSideDynamicsProcess::clear()
{
    envelope[0] = envelope[1] = 1.0f;
    vars->setDynamicGain(1.0f, 1.0f);
}

void MidSideDynamicsProcess::cacheProcessVariables()
{
    threshold = vars->getThreshold();
    attack = vars->getAttack();
    release = vars->getRelease();
    makeupGain = vars->getGain();
}

int32_t MidSideDynamicsProcess::processAudio(ctoot::audio::core::AudioBuffer* buffer)
{
	auto bypassed = vars->isBypassed();
	if (bypassed) {
		if (!wasBypassed) {
			clear();
		}
		wasBypassed = true;
		return AUDIO_OK;
	}
	auto sr = static_cast<int32_t>(buffer->getSampleRate());
	if (sr != sampleRate) {
		sampleRate = sr;
		vars->update(sr);
	}
	cacheProcessVariables();
	auto targetGainM = 1.0f;
	auto targetGainS = 1.0f;
	auto gainM = 0.0f;
	auto gainS = 0.0f;
	auto len = buffer->getSampleCount();
	auto mslen = static_cast<int32_t>((buffer->getSampleRate() * 0.001f));
	auto sumdiv = 1.0f / (mslen + mslen);
	if (!buffer->encodeMidSide())
		return AUDIO_OK;

	samplesM = buffer->getChannel(0);
	samplesS = buffer->getChannel(1);
	for (auto i = int32_t(0); i < len; i++) {
		float keyM = int32_t(0);
		float keyS = int32_t(0);
		if (isPeak) {
			keyM = ctoot::dsp::FastMath::max(keyM, abs((*samplesM)[i]));
			keyS = ctoot::dsp::FastMath::max(keyS, abs((*samplesS)[i]));
			targetGainM = function(0, keyM);
			targetGainS = function(1, keyS);
		}
		else if ((i % mslen) == 0 && (i + mslen) < len) {
			auto sumOfSquaresM = 0.0f;
			auto sumOfSquaresS = 0.0f;
			for (int32_t j = int32_t(0), k = i; j < mslen; j++, k++) {
				sumOfSquaresM += (*samplesM)[k] * (*samplesM)[k];
				sumOfSquaresS += (*samplesS)[k] * (*samplesS)[k];
			}
			squaresumsM[nsqsum] = sumOfSquaresM * sumdiv;
			squaresumsS[nsqsum] = sumOfSquaresS * sumdiv;
			float meanM = int32_t(0);
			float meanS = int32_t(0);
			for (auto s = int32_t(0); s < NSQUARESUMS; s++) {
				meanM += squaresumsM[s];
				meanS += squaresumsS[s];
			}
			if (++nsqsum >= NSQUARESUMS)
				nsqsum = 0;

			targetGainM = function(0, static_cast<float>(sqrt(meanM / NSQUARESUMS)));
			targetGainS = function(1, static_cast<float>(sqrt(meanS / NSQUARESUMS)));
		}
		gainM = dynamics(0, targetGainM);
		gainS = dynamics(1, targetGainS);
		(*samplesM)[i] *= gainM * makeupGain[0];
		(*samplesS)[i] *= gainS * makeupGain[1];
	}
	buffer->decodeMidSide();
	vars->setDynamicGain(gainM, gainS);
	wasBypassed = bypassed;
	return AUDIO_OK;
}

float MidSideDynamicsProcess::dynamics(int32_t i, float target)
{
	auto factor = target < envelope[i] ? attack[i] : release[i];
	envelope[i] = factor * (envelope[i] - target) + target;
	return envelope[i];
}
