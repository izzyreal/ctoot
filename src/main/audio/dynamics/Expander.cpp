#include <audio/dynamics/Expander.hpp>

using namespace ctoot::audio::dynamics;

Expander::Expander(DynamicsVariables* vars)
	: DynamicsProcess(vars, false)
{
}

float Expander::function(float value)
{
    return 1.0f;
}
