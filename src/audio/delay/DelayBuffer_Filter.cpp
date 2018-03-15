#include <audio/delay/DelayBuffer_Filter.hpp>

#include <audio/core/FloatDenormals.hpp>
#include <audio/delay/DelayBuffer.hpp>

using namespace ctoot::audio::delay;
using namespace std;

DelayBuffer_Filter::DelayBuffer_Filter(DelayBuffer *DelayBuffer_this) {
	this->DelayBuffer_this = DelayBuffer_this;
}

float ctoot::audio::delay::DelayBuffer_Filter::filter(float sample)
{
    zm1 = ctoot::audio::core::FloatDenormals::zeroDenorm(zm1 + DelayBuffer_this->lowpassK * (sample - zm1));
    return zm1;
}
