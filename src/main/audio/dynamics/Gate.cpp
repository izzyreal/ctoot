#include <audio/dynamics/Gate.hpp>

#include <audio/dynamics/DynamicsVariables.hpp>

using namespace ctoot::audio::dynamics;

Gate::Gate(DynamicsVariables* vars)
	: DynamicsProcess(vars, false)
{
}

void Gate::cacheProcessVariables()
{
    DynamicsProcess::cacheProcessVariables();
    depth = vars->getDepth();
    hold = vars->getHold();
    hysteresis = vars->getHysteresis();
}

float Gate::function(float value)
{
	if (open_) {
		if (value < threshold * hysteresis) {
			if (holdCount > 0) {
				holdCount -= 1;
				return 1.0f;
			}
			open_ = false;
		}
	}
	else {
		if (value > threshold) {
			holdCount = hold;
			open_ = true;
		}
	}
	return open_ ? 1.0f : depth;
}
