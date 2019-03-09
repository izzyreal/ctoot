#include <synth/modules/filter/FormantFilter.hpp>

#include <synth/modules/filter/FormantFilterVariables.hpp>
#include <synth/modules/filter/StateVariableFilterElement.hpp>

using namespace ctoot::synth::modules::filter;

FormantFilter::FormantFilter(FormantFilterVariables* vars)
{
	this->vars = vars;
	nBands = vars->size();
	for (int i = 0; i < nBands; i++) {
		auto element = new StateVariableFilterElement();
		element->bp = true;
		filters.push_back(element);
	}
	fn = std::vector<float>(nBands);
	level = std::vector<float>(nBands);
}

float FormantFilter::filter(float sample)
{
	float out = 0.0f;
	for (int i = 0; i < filters.size(); i++) {
		auto filter = filters[i];
		out += filter->filter(sample, fn[i], res) * level[i];
		i += 1;
	}
	return out;
}

void FormantFilter::setSampleRate(int32_t rate)
{
    vars->setSampleRate(rate);
}

void FormantFilter::update()
{
	auto fshift = vars->getFreqencyShift();
	res = 1.0f - vars->getResonance();
	for (int i = 0; i < nBands; i++) {
		level[i] = vars->getLevel(i);
		fn[i] = vars->getFrequency(i) * fshift;
	}
}
