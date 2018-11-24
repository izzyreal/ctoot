#include <audio/dynamics/Compressor.hpp>

#include <audio/dynamics/DynamicsVariables.hpp>
#include <dsp/FastMath.hpp>

#include <cmath>

using namespace ctoot::audio::dynamics;

Compressor::Compressor(DynamicsVariables* vars)
	: DynamicsProcess(vars, false)
{
}

void Compressor::cacheProcessVariables()
{
	DynamicsProcess::cacheProcessVariables();
	ratio2 = 1.0f - vars->getInverseRatio();
	inverseThreshold = vars->getInverseThreshold();
}

float Compressor::function(float value)
{
	if (value > threshold) {
		return 1.0f / static_cast<float>(pow(value * inverseThreshold, ratio2));
	}
	return 1.0f;
}
