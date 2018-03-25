#include <synth/modules/filter/AbstractSynthFilter.hpp>
#include <synth/modules/filter/FilterVariables.hpp>

using namespace ctoot::synth::modules::filter;

AbstractFilter::AbstractFilter(FilterVariables* filterVariables) 
{
	vars = filterVariables;
}

void AbstractFilter::setSampleRate(int rate)
{
    vars->setSampleRate(rate);
    fs = rate;
}
