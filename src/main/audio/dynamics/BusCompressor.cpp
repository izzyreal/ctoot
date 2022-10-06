#include <audio/dynamics/BusCompressor.hpp>

#include <dsp/VolumeUtils.hpp>
#include <audio/dynamics/DynamicsVariables.hpp>

#include <cmath>

using namespace ctoot::audio::dynamics;

BusCompressor::BusCompressor(DynamicsVariables* vars)
	: ClassicDynamicsProcess(vars)
{
}

void BusCompressor::cacheProcessVariables()
{
    ClassicDynamicsProcess::cacheProcessVariables();
    inverseRatio = vars->getInverseRatio();
    thresholddB = vars->getThresholddB();
    kneedB = vars->getKneedB();
    deriveLocalVariables();
}

void BusCompressor::deriveLocalVariables()
{
    auto twoKneedB = kneedB * int32_t(2);
    halfInverseKneedB = 1.0f / twoKneedB;
    y1 = thresholddB - kneedB;
    y2 = thresholddB + inverseRatio * kneedB;
    m1 = twoKneedB;
    m2 = twoKneedB * inverseRatio;
    thresholdMinusKneedB = thresholddB - kneedB;
    thresholdPlusKneedB = thresholddB + kneedB;
    oneMinusInverseRatio = 1.0f - inverseRatio;
}

float BusCompressor::function(float value)
{
    if(value < threshold * 0.1f)
        return 0.0f;

    auto dB = static_cast< float >(ctoot::dsp::VolumeUtils::lin2log(value * inverseThreshold));
    if(dB <= thresholdMinusKneedB) {
        return 0.0f;
    } else if(dB >= thresholdPlusKneedB) {
        return (dB - thresholddB) * oneMinusInverseRatio;
    }
    auto t = (dB - thresholdMinusKneedB) * halfInverseKneedB;
    auto t2 = t * t;
    auto t3 = t2 * t;
    return dB - ((t3 - int32_t(2) * t2 + t) * m1 + (int32_t(2) * t3 - int32_t(3) * t2 + int32_t(1)) * y1 + (-int32_t(2) * t3 + int32_t(3) * t2) * y2 + (t3 - t2) * m2);
}

float BusCompressor::dynamics(float target)
{
    target += 0.001f;
    auto factor = target > envelope ? attack : release;
    envelope = factor * (envelope - target) + target;
    return static_cast< float >(pow(10, -envelope * 0.05f));
}
