#include <synth/modules/oscillator/LFO.hpp>

#include <dsp/FastMath.hpp>
#include <synth/modules/oscillator/LFOVariables.hpp>

#include <cmath>
#include <cstdlib>

#define _USE_MATH_DEFINES
#include <math.h>

using namespace ctoot::synth::modules::oscillator;
using namespace  ctoot::dsp;

LFO::LFO(LFOVariables* vars, float initPhase)
	: LFO(vars)
{
    modulatorPhase = initPhase;
}

LFO::LFO(LFOVariables* vars)
{
    this->vars = vars;
    auto spread = vars->getDeviation();
    rateDelta = spread * static_cast<float>(rand()) - spread / 2;
    setSampleRate(44100);
}

void LFO::setSampleRate(int32_t sampleRate)
{
    xDelta = static_cast<float>(2 * M_PI / sampleRate);
}

void LFO::update()
{
    phaseDelta = xDelta * (vars->getFrequency() + rateDelta);
    shape = vars->isSine() ? 0 : 1;
}

float ctoot::synth::modules::oscillator::LFO::getSample()
{
	modulatorPhase += static_cast<float>(phaseDelta);
	if (modulatorPhase > M_PI) {
		modulatorPhase -= static_cast<float>(2 * M_PI);
	}
	return (shape == 0) ? FastMath::sin(modulatorPhase) : FastMath::triangle(modulatorPhase);
}
