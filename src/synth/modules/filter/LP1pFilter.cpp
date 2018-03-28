#include <synth/modules/filter/LP1pFilter.hpp>

#include <audio/core/FloatDenormals.hpp>

#define _USE_MATH_DEFINES
#include <math.h>

using namespace ctoot::synth::modules::filter;

LP1pFilter::LP1pFilter(float freq, int32_t rate)
{
    g = 1.0f - exp(-2.0 * M_PI * freq / rate);
}

float ctoot::synth::modules::filter::LP1pFilter::filter(float sample)
{
    y1 = ctoot::audio::core::FloatDenormals::zeroDenorm(y1 + g * (sample - y1));
    return y1;
}
