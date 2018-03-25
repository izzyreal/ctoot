#include <audio/dynamics/VariMuCompressorControls.hpp>

#include <audio/dynamics/DynamicsIds.hpp>
#include <control/ControlLaw.hpp>
#include <control/LogLaw.hpp>

using namespace ctoot::audio::dynamics;
using namespace std;

weak_ptr<ctoot::control::ControlLaw> VariMuCompressorControls::RELEASE_LAW()
{
	static auto res = make_shared<ctoot::control::LogLaw>(30.0f, 3000.0f, "ms");
	return res;
}

VariMuCompressorControls::VariMuCompressorControls()
	: DynamicsControls(DynamicsIds::VARI_MU_COMPRESSOR, "Vari.Mu.Comp")
{
	init();
}

VariMuCompressorControls::VariMuCompressorControls(std::string name, int32_t idOffset)
	: DynamicsControls(DynamicsIds::VARI_MU_COMPRESSOR, name, idOffset)
{
	init();
}

ctoot::control::ControlLaw* VariMuCompressorControls::getReleaseLaw()
{
	return RELEASE_LAW().lock().get();
}

bool VariMuCompressorControls::hasGainReductionIndicator()
{
    return true;
}

bool VariMuCompressorControls::hasDryGain()
{
    return true;
}

bool VariMuCompressorControls::hasGain()
{
    return true;
}

bool VariMuCompressorControls::isRMS()
{
    return false;
}
