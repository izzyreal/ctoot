#include <audio/dynamics/ClassicDynamicsProcess.hpp>

#include <audio/core/AudioBuffer.hpp>
#include <audio/dynamics/DynamicsVariables.hpp>
#include <dsp/FastMath.hpp>

using namespace ctoot::audio::dynamics;
using namespace std;

void ClassicDynamicsProcess::init()
{
    envelope = 1.0f;
    gain = 1.0f;
    isPeak = true;
    sampleRate = int32_t(0);
    samples = vector<vector<float>*>(6);
}

ClassicDynamicsProcess::ClassicDynamicsProcess(DynamicsVariables* vars)
{
    init();
    this->vars = vars;
    wasBypassed = !vars->isBypassed();
}

ClassicDynamicsProcess::ClassicDynamicsProcess()
{
    init();
}

void ClassicDynamicsProcess::clear()
{
    envelope = 1.0f;
    gain = 1.0f;
    vars->setDynamicGain(1.0f);
}

void ClassicDynamicsProcess::cacheProcessVariables()
{
    threshold = vars->getThreshold();
    inverseThreshold = vars->getInverseThreshold();
    attack = vars->getAttack();
    release = vars->getRelease();
    makeupGain = vars->getGain();
    dryGain = vars->getDryGain();
}

int32_t ClassicDynamicsProcess::processAudio(ctoot::audio::core::AudioBuffer* buffer)
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
	auto len = buffer->getSampleCount();
	auto nc = buffer->getChannelCount();
	for (auto c = int32_t(0); c < nc; c++) {
		samples[c] = buffer->getChannel(c);
	}
	if (vars->isRMS()) {
		for (auto i = int32_t(0); i < len; i++) {
			float key = int32_t(0);
			for (auto c = int32_t(0); c < nc; c++) {
				key += (*samples[c])[i] * (*samples[c])[i];
			}
			gain = static_cast<float>(sqrt(dynamics(function(key))));
			for (auto c = int32_t(0); c < nc; c++) {
				(*samples[c])[i] *= (gain * makeupGain) + dryGain;
			}
		}
	}
	else {
		float key = int32_t(0);
		for (auto i = int32_t(0); i < len; i++) {
			for (auto c = int32_t(0); c < nc; c++) {
				key = ctoot::dsp::FastMath::max(key, abs((*samples[c])[i]));
			}
			gain = dynamics(function(key));
			for (auto c = int32_t(0); c < nc; c++) {
				(*samples[c])[i] *= (gain * makeupGain) + dryGain;
			}
		}
	}
	vars->setDynamicGain(gain);
	wasBypassed = bypassed;
	return AUDIO_OK;
}

float ClassicDynamicsProcess::dynamics(float target)
{
    auto factor = target < envelope ? attack : release;
    envelope = factor * (envelope - target) + target;
    return envelope;
}
