#include <audio/dynamics/LimiterControls.hpp>

#include <audio/dynamics/DynamicsIds.hpp>
#include <control/LogLaw.hpp>

using namespace ctoot::audio::dynamics;
using namespace std;

weak_ptr<ctoot::control::ControlLaw> LimiterControls::RELEASE_LAW()
{
	static auto res = make_shared<ctoot::control::LogLaw>(20.0f, 2000.0f, "ms");
	return res;
}

LimiterControls::LimiterControls()
	: DynamicsControls(DynamicsIds::LIMITER_ID, "Limiter")
{
	init();
}

ctoot::control::ControlLaw* LimiterControls::getReleaseLaw()
{
	return RELEASE_LAW().lock().get();
}

bool LimiterControls::hasGainReductionIndicator()
{
    return true;
}
