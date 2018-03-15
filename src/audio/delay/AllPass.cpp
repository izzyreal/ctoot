#include <audio/delay/AllPass.hpp>

#include <audio/core/FloatDenormals.hpp>
#include <audio/delay/PhaserProcess.hpp>

using namespace ctoot::audio::delay;

AllPass::AllPass(PhaserProcess *PhaserProcess_this)
{
	this->PhaserProcess_this = PhaserProcess_this;
}

float AllPass::update(float in)
{
    auto y = in * -PhaserProcess_this->a1 + zm1;
    zm1 = ctoot::audio::core::FloatDenormals::zeroDenorm(y * PhaserProcess_this->a1 + in);
    return y;
}
