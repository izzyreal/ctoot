#include <synth/modules/filter/HP1pFilter.hpp>

using namespace ctoot::synth::modules::filter;

HP1pFilter::HP1pFilter(float freq, int32_t rate)
	: LP1pFilter(freq, rate)
{    
}

float HP1pFilter::filter(float sample)
{
    return sample - LP1pFilter::filter(sample);
}
