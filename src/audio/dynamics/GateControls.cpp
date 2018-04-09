#include <audio/dynamics/GateControls.hpp>

#include <audio/dynamics/DynamicsIds.hpp>
#include <control/ControlLaw.hpp>
#include <control/LinearLaw.hpp>

using namespace ctoot::audio::dynamics;
using namespace ctoot::control;
using namespace std;

weak_ptr<ctoot::control::ControlLaw> GateControls::THRESH_LAW()
{
	static auto res = make_shared<ctoot::control::LinearLaw>(-80.0f, 20.0f, "dB");
	return res;
}

GateControls::GateControls()
	: DynamicsControls(DynamicsIds::GATE_ID, "Gate")
{
	init();
}

weak_ptr<ControlLaw> GateControls::getThresholdLaw()
{
	return THRESH_LAW();
}

bool GateControls::hasHold()
{
    return true;
}

bool GateControls::hasDepth()
{
    return true;
}

bool GateControls::hasHysteresis()
{
    return true;
}
