#include <audio/dynamics/CompressorControls.hpp>

#include <audio/dynamics/DynamicsIds.hpp>
#include <control/ControlLaw.hpp>
#include <control/LogLaw.hpp>

using namespace ctoot::audio::dynamics;
using namespace ctoot::control;
using namespace std;

weak_ptr<ControlLaw> CompressorControls::ATTACK_LAW()
{
	static auto res = make_shared<LogLaw>(10.0f, 100.0f, "ms");
	return res;
}

CompressorControls::CompressorControls()
	: DynamicsControls(DynamicsIds::COMPRESSOR_ID, "Compressor")
{
	init();
}

CompressorControls::CompressorControls(std::string name, int32_t idOffset)
	: DynamicsControls(DynamicsIds::COMPRESSOR_ID, name, idOffset)
{
	init();
}

weak_ptr<ControlLaw> CompressorControls::getAttackLaw()
{
    return ATTACK_LAW();
}

bool CompressorControls::hasGainReductionIndicator()
{
    return true;
}

bool CompressorControls::hasRatio()
{
    return true;
}

bool CompressorControls::hasGain()
{
    return true;
}

bool CompressorControls::hasDryGain()
{
    return true;
}

bool CompressorControls::hasKey()
{
    return true;
}
