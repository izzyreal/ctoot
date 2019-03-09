#include <audio/dynamics/BusCompressorControls.hpp>

#include <audio/dynamics/DynamicsIds.hpp>
#include <control/ControlLaw.hpp>
#include <control/LogLaw.hpp>

using namespace ctoot::audio::dynamics;
using namespace ctoot::control;
using namespace std;

weak_ptr<ControlLaw> BusCompressorControls::ATTACK_LAW()
{
	static auto res = make_shared<LogLaw>(0.1f, 30.0f, "ms");
    return res;
}

weak_ptr<ControlLaw> BusCompressorControls::RELEASE_LAW()
{
	static auto res = make_shared<LogLaw>(30.0f, 3000.0f, "ms");
	return res;
}

BusCompressorControls::BusCompressorControls()
	: DynamicsControls(DynamicsIds::BUS_COMPRESSOR, "Bus.Comp")
{
	init();
}

BusCompressorControls::BusCompressorControls(string name, int32_t idOffset)
	: DynamicsControls(DynamicsIds::BUS_COMPRESSOR, name, idOffset)
{
	init();
}

weak_ptr<ControlLaw> BusCompressorControls::getAttackLaw()
{
	return ATTACK_LAW();
}

weak_ptr<ControlLaw> BusCompressorControls::getReleaseLaw()
{
    return RELEASE_LAW();
}

bool BusCompressorControls::hasGainReductionIndicator()
{
    return true;
}

bool BusCompressorControls::hasDryGain()
{
    return true;
}

bool BusCompressorControls::hasGain()
{
    return true;
}

bool BusCompressorControls::hasKnee()
{
    return true;
}

bool BusCompressorControls::hasInverseRatio()
{
    return true;
}

bool BusCompressorControls::hasRMS()
{
    return true;
}
