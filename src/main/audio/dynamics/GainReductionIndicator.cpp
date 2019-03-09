#include <audio/dynamics/GainReductionIndicator.hpp>

#include <control/LinearLaw.hpp>

using namespace ctoot::audio::dynamics;
using namespace std;

weak_ptr<ctoot::control::LinearLaw> GainReductionIndicator::GR_LAW()
{
	static auto res = make_shared<ctoot::control::LinearLaw>(-20.f, 0.f, "dB");
	return res;
}

GainReductionIndicator::GainReductionIndicator()
	: ctoot::control::FloatControl(-1, "Gain Reduction", GR_LAW(), 3.f, 0.f)

{
    indicator = true;
    setHidden(true);
}
