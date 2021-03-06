#include <audio/dynamics/ExpanderControls.hpp>

#include <audio/dynamics/DynamicsIds.hpp>
#include <control/ControlLaw.hpp>
#include <control/LinearLaw.hpp>

using namespace ctoot::audio::dynamics;
using namespace ctoot::control;
using namespace std;

weak_ptr<ctoot::control::ControlLaw> ExpanderControls::THRESH_LAW()
{
	static auto res = make_shared<ctoot::control::LinearLaw>(-60.0f, 20.0f, "dB");
	return res;
}

ExpanderControls::ExpanderControls()
	: DynamicsControls(DynamicsIds::EXPANDER_ID, "Expander")
{
	init();
}

weak_ptr<ControlLaw> ExpanderControls::getThresholdLaw()
{
	return THRESH_LAW();
}

bool ExpanderControls::hasRatio()
{
    return true;
}
