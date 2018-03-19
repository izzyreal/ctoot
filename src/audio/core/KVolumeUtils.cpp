#include "KVolumeUtils.hpp"

#include <dsp/VolumeUtils.hpp>

using namespace ctoot::audio::core;

constexpr double KVolumeUtils::K;

double KVolumeUtils::lin2log(double dLinear)
{
	return ctoot::dsp::VolumeUtils::VolumeUtils::lin2log(dLinear) + K;
}

double KVolumeUtils::log2lin(double dLogarithmic)
{
    return ctoot::dsp::VolumeUtils::log2lin(dLogarithmic - K);
}
