#include <synth/modules/filter/DualStateVariableFilterControls.hpp>

#include <control/Control.hpp>
#include <control/EnumControl.hpp>
#include <synth/modules/filter/DualStateVariableFilterConfig.hpp>
#include <synth/modules/filter/DualStateVariableFilterControlsTypeControl.hpp>
#include <synth/modules/filter/FilterControlIds.hpp>
#include <synth/modules/filter/FilterIds.hpp>

using namespace ctoot::synth::modules::filter;
using namespace std;

DualStateVariableFilterControls::DualStateVariableFilterControls(int32_t instanceIndex, std::string name, int32_t idOffset)
	: FilterControls(FilterIds::DUAL_STATE_VARIABLE_FILTER_ID, instanceIndex, name, idOffset)
{
}

void DualStateVariableFilterControls::derive(ctoot::control::Control* c)
{
	switch (c->getId() - idOffset) {
	case FilterControlIds::TYPE:
		type = deriveType();
		break;
	default:
		FilterControls::derive(c);
		break;
	}
}

void DualStateVariableFilterControls::createControls()
{
    FilterControls::createControls();
	auto tc = createTypeControl();
	typeControl = tc;
	add(std::move(tc));
}

void DualStateVariableFilterControls::deriveSampleRateIndependentVariables()
{
    FilterControls::deriveSampleRateIndependentVariables();
    type = deriveType();
}

float DualStateVariableFilterControls::deriveResonance()
{
    return static_cast< float >((2 * (1.0f - pow(FilterControls::deriveResonance(), 0.25))));
}

 DualStateVariableFilterConfig* ctoot::synth::modules::filter::DualStateVariableFilterControls::deriveType()
{
    return boost::any_cast<DualStateVariableFilterConfig*>(typeControl.lock()->getValue());
}

shared_ptr<ctoot::control::EnumControl> ctoot::synth::modules::filter::DualStateVariableFilterControls::createTypeControl()
{
    return make_shared<DualStateVariableFilterControlsTypeControl>(FilterControlIds::TYPE + idOffset, string("Type"));
}

 ctoot::synth::modules::filter::DualStateVariableFilterConfig* ctoot::synth::modules::filter::DualStateVariableFilterControls::getType()
{
    return type;
}

float ctoot::synth::modules::filter::DualStateVariableFilterControls::getCutoff()
{
    return FilterControls::getCutoff();
}

float ctoot::synth::modules::filter::DualStateVariableFilterControls::getResonance()
{
    return FilterControls::getResonance();
}

void DualStateVariableFilterControls::setSampleRate(int32_t rate)
{
    FilterControls::setSampleRate(rate);
}
