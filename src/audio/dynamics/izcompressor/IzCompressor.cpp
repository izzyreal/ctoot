#include <audio/dynamics/izcompressor/IzCompressor.hpp>

#include <audio/dynamics/izcompressor/IzCompressorProcessVariables.hpp>

#include <Logger.hpp>

using namespace ctoot::audio::dynamics;
using namespace ctoot::audio::dynamics::izcompressor;
using namespace std;

IzCompressor::IzCompressor(IzCompressorProcessVariables* vars)
	: IzCompressorProcess(vars, false)
{
}

void IzCompressor::cacheProcessVariables()
{
	IzCompressorProcess::cacheProcessVariables();
	auto cl = vars->getLink().lock();
	inverseRatio = cl ? cl->getInverseRatio() : vars->getInverseRatio();
	ratio = 1.0f - inverseRatio;
	inverseThreshold = cl ? cl->getInverseThreshold() : vars->getInverseThreshold();
}

float IzCompressor::function(float value)
{
	if (value > threshold) {
		return 1.0f / static_cast<float>(pow(value * inverseThreshold, ratio));
	}
	return 1.0f;
}
