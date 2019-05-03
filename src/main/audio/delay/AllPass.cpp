#include <audio/delay/AllPass.hpp>

#include <audio/core/FloatDenormals.hpp>
#include <audio/delay/PhaserProcess.hpp>

using namespace ctoot::audio::delay;
using namespace ctoot::audio::core;

AllPass::AllPass(const PhaserProcess* _phaserProcess) : phaserProcess(_phaserProcess)
{
}

float AllPass::update(float in)
{
    auto y = in * -phaserProcess->a1 + zm1;
    zm1 = FloatDenormals::zeroDenorm(y * phaserProcess->a1 + in);
    return y;
}
