#include <synth/modules/filter/MoogFilter2.hpp>

#include <synth/modules/filter/FilterVariables.hpp>
#include <synth/modules/filter/MoogFilterElement.hpp>

using namespace ctoot::synth::modules::filter;

MoogFilter2::MoogFilter2(FilterVariables* variables)
	: AbstractFilter(variables)
{
    element = new MoogFilterElement();
}

float ctoot::synth::modules::filter::MoogFilter2::update()
{
    res = vars->getResonance();
    return vars->getCutoff();
}

float ctoot::synth::modules::filter::MoogFilter2::filter(float sample, float f)
{
	if (f > 1.0f)
		f = 1.0f;

	return element->filter(sample, f, res);
}
