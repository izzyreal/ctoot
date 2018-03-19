#include <audio/filter/FilterTools.hpp>

#include <cmath>

using namespace ctoot::audio::filter;

float& FilterTools::LN2()
{
    return LN2_;
}
float FilterTools::LN2_ = static_cast< float >(log(2));

float FilterTools::getDampingFactor(float resonance)
{
    return 1.0f / resonance;
}

float FilterTools::getHzBandwidth(float frequency, float resonance)
{
    return frequency / resonance;
}

float FilterTools::getOctaveBandwidth(float resonance)
{
    auto a = 1.0 / (2 * resonance);
    auto b = sqrt((a * a) + 1);
    return static_cast< float >((2 * log(a + b) / LN2_));
}
