#include "StateVariableFilterControls.hpp"
#include "control/Control.hpp"
#include "control/LawControl.hpp"
#include "control/LinearLaw.hpp"

#include <cmath>

using namespace ctoot::synth::modules::filter;
using namespace std;

StateVariableFilterControls::StateVariableFilterControls(string name, int idOffset)
	: FilterControls(34, name, idOffset)
{
}

void StateVariableFilterControls::derive(ctoot::control::Control* c)
{
	FilterControls::derive(c);
}

void StateVariableFilterControls::deriveSampleRateIndependentVariables()
{
    FilterControls::deriveSampleRateIndependentVariables();
}

float StateVariableFilterControls::deriveResonance()
{
    return static_cast< float >(2 * (1.0f - pow(FilterControls::deriveResonance(), 0.25)));
}
