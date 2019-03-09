#include <synth/modules/oscillator/UnisonControls.hpp>

#include <control/Control.hpp>
#include <control/FloatControl.hpp>
#include <control/IntegerControl.hpp>
#include <control/IntegerLaw.hpp>
#include <control/LinearLaw.hpp>
#include <synth/modules/oscillator/OscillatorIds.hpp>

using namespace ctoot::synth::modules::oscillator;
using namespace std;

weak_ptr<ctoot::control::IntegerLaw> UnisonControls::OSC_COUNT_LAW()
{
	static auto res = make_shared<ctoot::control::IntegerLaw>(1, 32, "");
	return res;
}

weak_ptr<ctoot::control::LinearLaw> UnisonControls::SPREAD_LAW()
{
	return ctoot::control::LinearLaw::UNITY();
}

UnisonControls::UnisonControls(int32_t idOffset)
	: ctoot::control::CompoundControl(OscillatorIds::UNISON_ID, 0, "Unison")
{
	this->idOffset = idOffset;
	createControls();
	deriveSampleRateIndependentVariables();
}

void UnisonControls::derive(ctoot::control::Control* c)
{
	switch (c->getId() - idOffset) {
	case OSC_COUNT:
		oscillatorCount = deriveOscillatorCount();
		break;
	case PITCH_SPREAD:
		pitchSpread = derivePitchSpread();
		break;
	case PHASE_SPREAD:
		phaseSpread = derivePhaseSpread();
		break;
	}
}

void UnisonControls::createControls()
{
	auto occ = createOscillatorCountControl();
	oscillatorCountControl = occ;
	derive(occ.get());
	add(std::move(occ));

	auto pc = createPitchSpreadControl();
	pitchSpreadControl = pc;
	derive(pc.get());
	add(std::move(pc));

	auto psc = createPhaseSpreadControl();
	phaseSpreadControl = psc;
	derive(psc.get());
	add(std::move(psc));
}

shared_ptr<ctoot::control::IntegerControl> UnisonControls::createOscillatorCountControl()
{
    auto control = make_shared<ctoot::control::IntegerControl>(OSC_COUNT + idOffset, "Oscs", OSC_COUNT_LAW(), 1.0f, 1);
    return control;
}

shared_ptr<ctoot::control::FloatControl> UnisonControls::createPitchSpreadControl()
{
    auto control = make_shared<ctoot::control::FloatControl>(PITCH_SPREAD + idOffset, "Detune", SPREAD_LAW(), 0.01f, 0.0f);
    return control;
}

shared_ptr<ctoot::control::FloatControl> UnisonControls::createPhaseSpreadControl()
{
    auto control = make_shared<ctoot::control::FloatControl>(PHASE_SPREAD + idOffset, "Phase", SPREAD_LAW(), 0.01f, 1.0f);
    return control;
}

void UnisonControls::deriveSampleRateIndependentVariables()
{
	oscillatorCount = deriveOscillatorCount();
	pitchSpread = derivePitchSpread();
	phaseSpread = derivePhaseSpread();
}

int32_t UnisonControls::deriveOscillatorCount()
{
    return oscillatorCountControl.lock()->getUserValue();
}

float UnisonControls::derivePitchSpread()
{
    return pitchSpreadControl.lock()->getValue();
}

float UnisonControls::derivePhaseSpread()
{
    return phaseSpreadControl.lock()->getValue();
}

int32_t UnisonControls::getOscillatorCount()
{
    return oscillatorCount;
}

float UnisonControls::getPitchSpread()
{
    return pitchSpread;
}

float UnisonControls::getPhaseSpread()
{
    return phaseSpread;
}
