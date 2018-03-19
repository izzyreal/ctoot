#include <audio/dynamics/TremoloProcess.hpp>
#include <audio/core/AudioBuffer.hpp>
#include <audio/dynamics/TremoloProcessVariables.hpp>
#include <dsp/FastMath.hpp>

#define _USE_MATH_DEFINES
#include <math.h>

using namespace ctoot::audio::dynamics;
using namespace std;

void TremoloProcess::init()
{
    samples = vector<vector<float>*>(8);
    lfoPhase = 0.0f;
}

TremoloProcess::TremoloProcess(TremoloProcessVariables* variables)
{
    init();
    vars = variables;
}

int32_t TremoloProcess::processAudio(ctoot::audio::core::AudioBuffer* buffer)
{
    if(vars->isBypassed())
        return AUDIO_OK;

    auto ns = buffer->getSampleCount();
    auto nc = buffer->getChannelCount();
    for (auto c = int32_t(0); c < nc; c++) {
		samples[c] = buffer->getChannel(c);
    }
    auto _lfoInc = int32_t(2) * static_cast< float >(M_PI) * (vars->getRate() / buffer->getSampleRate());
    auto depth = vars->getDepth();
    float mod;
    for (auto s = int32_t(0); s < ns; s++) {
        mod = int32_t(1) - depth * ((ctoot::dsp::FastMath::sin(lfoPhase) + 1.0f) * 0.5f);
        lfoPhase += _lfoInc;
        if(lfoPhase >= M_PI)
            lfoPhase -= M_PI * int32_t(2);

        for (auto c = int32_t(0); c < nc; c++) {
            (*samples[c])[s] *= mod;
        }
    }
    return AUDIO_OK;
}
