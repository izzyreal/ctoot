#include <synth/modules/filter/LP1pHP1pControls.hpp>

#include <control/Control.hpp>
#include <control/FloatControl.hpp>
#include <control/LogLaw.hpp>

using namespace ctoot::synth::modules::filter;
using namespace std;

weak_ptr<ctoot::control::ControlLaw> ctoot::synth::modules::filter::LP1pHP1pControls::LP_LAW()
{
	static auto res = make_shared <ctoot::control::LogLaw>(1.0f, 16.0f, "");
	return res;
}

weak_ptr<ctoot::control::ControlLaw> ctoot::synth::modules::filter::LP1pHP1pControls::HP_LAW()
{
	static auto res = make_shared<ctoot::control::LogLaw>(0.25f, 4.0f, "");
	return res;
}

LP1pHP1pControls::LP1pHP1pControls(int32_t id, int32_t instanceIndex, std::string name, int32_t idOffset)
	: ctoot::control::CompoundControl(id, instanceIndex, name)
{
    this->idOffset = idOffset;
    createControls();
    deriveSampleRateIndependentVariables();
    deriveSampleRateDependentVariables();
}

void LP1pHP1pControls::derive(ctoot::control::Control* c)
{
	switch (c->getId() - idOffset) {
	case LPRATIO:
		lpRatio = deriveLPRatio();
		break;
	case HPRATIO:
		hpRatio = deriveHPRatio();
		break;
	}
}

void LP1pHP1pControls::createControls()
{
	auto lprc = createLPRatioControl();
	lpRatioControl = lprc;
    add(std::move(lprc));
	
	auto hprc = createHPRatioControl();
	hpRatioControl = hprc;
    add(std::move(hprc));
}

void LP1pHP1pControls::deriveSampleRateIndependentVariables()
{
    lpRatio = deriveLPRatio();
    hpRatio = deriveHPRatio();
}

void LP1pHP1pControls::deriveSampleRateDependentVariables()
{
}

float LP1pHP1pControls::deriveLPRatio()
{
    return lpRatioControl.lock()->getValue();
}

float LP1pHP1pControls::deriveHPRatio()
{
    return hpRatioControl.lock()->getValue();
}

shared_ptr<ctoot::control::FloatControl> LP1pHP1pControls::createLPRatioControl()
{
    return make_shared<ctoot::control::FloatControl>(LPRATIO + idOffset, "LP", LP_LAW(), 1.0f, 4);
}

shared_ptr<ctoot::control::FloatControl> LP1pHP1pControls::createHPRatioControl()
{
	return make_shared<ctoot::control::FloatControl>(HPRATIO + idOffset, "HP", HP_LAW(), 0.1f, 1.0f);
}

void LP1pHP1pControls::setSampleRate(int32_t rate)
{
	if (sampleRate != rate) {
		sampleRate = rate;
		deriveSampleRateDependentVariables();
	}
}

float LP1pHP1pControls::getHighPassRatio()
{
    return hpRatio;
}

float LP1pHP1pControls::getLowPassRatio()
{
    return lpRatio;
}
