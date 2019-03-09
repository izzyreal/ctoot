#include <audio/dynamics/Limiter.hpp>

using namespace ctoot::audio::dynamics;

Limiter::Limiter(DynamicsVariables* vars)
	: DynamicsProcess(vars, true)
{
}

float Limiter::function(float value)
{
    return value > threshold ? threshold / value : 1.0f;
}
