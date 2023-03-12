#include <synth/modules/filter/StateVariableFilterControls.hpp>
#include <control/BooleanControl.hpp>
#include <control/Control.hpp>
#include <control/LawControl.hpp>
#include <control/LinearLaw.hpp>
#include <synth/modules/filter/FilterControlIds.hpp>

#include <cmath>

using namespace ctoot::synth::modules::filter;
using namespace std;

StateVariableFilterControls::StateVariableFilterControls(string name, int idOffset)
	: FilterControls(34, name, idOffset)
{
}

void StateVariableFilterControls::derive(ctoot::control::Control* c)
{
	switch (c->getId() - idOffset) {
	case FilterControlIds::MODE_MIX:
		modeMix = deriveModeMix();
		break;
	case FilterControlIds::BAND_MODE:
		bandMode = deriveBandMode();
		break;
	default:
		FilterControls::derive(c);
		break;
	}
}

void StateVariableFilterControls::createControls()
{
	modeMixControl = createModeMixControl();
	add(shared_ptr<Control>(modeMixControl));
	bandModeControl = createBandModeControl();
	add(shared_ptr<Control>(bandModeControl));
}

void StateVariableFilterControls::deriveSampleRateIndependentVariables()
{
    FilterControls::deriveSampleRateIndependentVariables();
    modeMix = deriveModeMix();
    bandMode = deriveBandMode();
}

float StateVariableFilterControls::deriveResonance()
{
    return static_cast< float >(2 * (1.0f - pow(FilterControls::deriveResonance(), 0.25)));
}

float StateVariableFilterControls::deriveModeMix()
{
    return modeMixControl->getValue();
}

bool StateVariableFilterControls::deriveBandMode()
{
    return bandModeControl->getValue();
}

ctoot::control::LawControl* StateVariableFilterControls::createModeMixControl()
{
    auto control = new ctoot::control::LawControl(FilterControlIds::MODE_MIX + idOffset, "Mix", ctoot::control::LinearLaw::UNITY(), 0.01f, 0.0f);
    return control;
}

ctoot::control::BooleanControl* StateVariableFilterControls::createBandModeControl()
{
	auto control = new ctoot::control::BooleanControl(FilterControlIds::BAND_MODE + idOffset, "Band.Pass", bandMode);
	control->setAnnotation("B");
	return control;
}

float StateVariableFilterControls::getModeMix()
{
    return modeMix;
}

bool StateVariableFilterControls::isBandMode()
{
    return bandMode;
}

float StateVariableFilterControls::getCutoff()
{
    return FilterControls::getCutoff();
}

float StateVariableFilterControls::getResonance()
{
    return FilterControls::getResonance();
}

void StateVariableFilterControls::setSampleRate(int rate)
{
    FilterControls::setSampleRate(rate);
}
