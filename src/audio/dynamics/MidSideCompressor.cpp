#include <audio/dynamics/MidSideCompressor.hpp>

#include <audio/dynamics/MidSideDynamicsProcessVariables.hpp>

using namespace ctoot::audio::dynamics;
using namespace std;

MidSideCompressor::MidSideCompressor(MidSideDynamicsProcessVariables* vars)
	: MidSideDynamicsProcess(vars, false)
{
}

void MidSideCompressor::cacheProcessVariables()
{
	MidSideDynamicsProcess::cacheProcessVariables();
	inverseRatio = vars->getInverseRatio();
	ratio2[0] = 1.0f - inverseRatio[0];
	ratio2[1] = 1.0f - inverseRatio[1];
	inverseThreshold = vars->getInverseThreshold();
}

float MidSideCompressor::function(int32_t i, float value)
{
	if (value > threshold[i]) {
		return 1.0f / static_cast<float>(pow(value * inverseThreshold[i], ratio2[i]));
	}
	return 1.0f;
}
