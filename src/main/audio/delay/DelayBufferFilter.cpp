#include <audio/delay/DelayBufferFilter.hpp>

#include <audio/core/FloatDenormals.hpp>
#include <audio/delay/DelayBuffer.hpp>

using namespace ctoot::audio::delay;
using namespace std;

DelayBufferFilter::DelayBufferFilter(DelayBuffer* _delayBuffer) : delayBuffer(_delayBuffer)
{
}

float ctoot::audio::delay::DelayBufferFilter::filter(float sample)
{
    zm1 = ctoot::audio::core::FloatDenormals::zeroDenorm(zm1 + delayBuffer->lowpassK * (sample - zm1));
    return zm1;
}
