#include <synth/modules/filter/DualStateVariableFilter.hpp>

#include <dsp/FastMath.hpp>
#include <synth/modules/filter/DualStateVariableFilterConfig.hpp>
#include <synth/modules/filter/DualStateVariableFilterElement.hpp>
#include <synth/modules/filter/DualStateVariableFilterVariables.hpp>
#include <synth/modules/filter/FilterType.hpp>
#include <synth/modules/filter/FilterVariables.hpp>

#define _USE_MATH_DEFINES
#include <math.h>

using namespace ctoot::synth::modules::filter;

DualStateVariableFilter::DualStateVariableFilter(DualStateVariableFilterVariables* variables)
	: AbstractFilter(variables)
{
    element = new DualStateVariableFilterElement();
}

float ctoot::synth::modules::filter::DualStateVariableFilter::update()
{
	config = dynamic_cast<DualStateVariableFilterVariables*>(vars)->getType();
	res = vars->getResonance();
	return vars->getCutoff();
}

float ctoot::synth::modules::filter::DualStateVariableFilter::filter(float sample, float fn1)
{
	auto f1 = 2.0f * ctoot::dsp::FastMath::sin(static_cast<float>((M_PI * ctoot::dsp::FastMath::min(0.24f, fn1 * 0.25f))));
	config->freq1 = f1;
	config->damp1 = ctoot::dsp::FastMath::min(res, ctoot::dsp::FastMath::min(1.9f, 2.0f / f1 - f1 * 0.5f));
	if (config->type2 > FilterType::OFF && config->f2ratio != 1.0f) {
		auto fn2 = fn1 * config->f2ratio;
		auto f2 = 2.0f * ctoot::dsp::FastMath::sin(static_cast<float>((M_PI * ctoot::dsp::FastMath::min(0.24f, fn2 * 0.25f))));
		config->freq2 = f2;
		config->damp2 = ctoot::dsp::FastMath::min(res, ctoot::dsp::FastMath::min(1.9f, 2.0f / f2 - f2 * 0.5f));
	}
	else {
		config->freq2 = config->freq1;
		config->damp2 = config->damp1;
	}
	return element->filter(sample, config);
}

DualStateVariableFilter::~DualStateVariableFilter() {
	delete element;
}
