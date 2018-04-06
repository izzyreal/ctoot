#include <audio/dynamics/IzCompressor.hpp>

#include <audio/dynamics/IzCompressorProcessVariables.hpp>

using namespace ctoot::audio::dynamics;
using namespace std;

IzCompressor::IzCompressor(IzCompressorProcessVariables* vars)
	: IzCompressorProcess(vars, false)
{
}

void IzCompressor::cacheProcessVariables()
{
	IzCompressorProcess::cacheProcessVariables();
	inverseRatio = vars->getInverseRatio();
	ratio = 1.0f - inverseRatio;
	inverseThreshold = vars->getInverseThreshold();
}

float IzCompressor::function(float value)
{
	if (value > threshold) {
		return 1.0f / static_cast<float>(pow(value * inverseThreshold, ratio));
	}
	return 1.0f;
}
