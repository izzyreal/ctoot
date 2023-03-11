#include "KVolumeUtils.hpp"

#include <dsp/VolumeUtils.hpp>

using namespace ctoot::audio::core;

constexpr double KVolumeUtils::K;

double KVolumeUtils::log2lin(double dLogarithmic)
{
    return ctoot::dsp::VolumeUtils::log2lin(dLogarithmic - K);
}
