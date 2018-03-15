#include <audio/delay/PhaserProcess.hpp>

#include <audio/core/AudioBuffer.hpp>
#include <audio/core/FloatDenormals.hpp>
#include <audio/delay/AllPass.hpp>
#include <audio/delay/PhaserProcessVariables.hpp>

#define _USE_MATH_DEFINES
#include <math.h>  

using namespace ctoot::audio::delay;
using namespace std;

constexpr int PhaserProcess::N;

PhaserProcess::PhaserProcess(PhaserProcessVariables* vars)
{
	allpass = vector<AllPass*>(N);
	zm1 = 0.0f;
	lfoPhase = 0.0f;
	sampleRate = -int(1);
	this->vars = vars;
	for (auto i = int(0); i < N; i++) {
		allpass[i] = new AllPass(this);
	}
}

int PhaserProcess::processAudio(ctoot::audio::core::AudioBuffer* buffer)
{
	if (vars->isBypassed())
		return AUDIO_OK;

	auto sr = static_cast<int>(buffer->getSampleRate());
	auto ns = buffer->getSampleCount();
	auto samples = buffer->getChannel(0);
	if (sr != sampleRate) {
		dmin = 440.0f / (sr / 2.0f);
		dmax = 1600.0f / (sr / 2.0f);
		sampleRate = sr;
	}
	auto n = vars->getStages();
	auto depth = vars->getDepth();
	auto fb = vars->getFeedback();
	auto _lfoInc = (float)(2) * M_PI * (vars->getRate() / sampleRate);
	for (auto i = int(0); i < ns; i++) {
		auto d = dmin + (dmax - dmin) * ((sin(lfoPhase) + 1.0f) * 0.5f);
		lfoPhase += _lfoInc;
		if (lfoPhase >= M_PI)
			lfoPhase -= M_PI * int(2);

		a1 = (1.0f - d) / (1.0f + d);
		auto y = (*samples)[i] + zm1 * fb;
		for (auto a = int(0); a < n; a++) {
			y = allpass[a]->update(y);
		}
		zm1 = ctoot::audio::core::FloatDenormals::zeroDenorm(y);
		(*samples)[i] += zm1 * depth;
	}
	return AUDIO_OK;
}

PhaserProcess::~PhaserProcess() {
	for (auto& a : allpass) {
		if (a != nullptr)
			delete a;
	}
}
