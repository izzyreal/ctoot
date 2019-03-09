#include <synth/modules/oscillator/DSFOscillatorControls.hpp>

#include <control/BooleanControl.hpp>
#include <control/Control.hpp>
#include <control/FloatControl.hpp>
#include <control/IntegerControl.hpp>
#include <control/IntegerLaw.hpp>
#include <control/LinearLaw.hpp>
#include <synth/modules/oscillator/OscillatorIds.hpp>

using namespace ctoot::synth::modules::oscillator;
using namespace std;

weak_ptr<ctoot::control::IntegerLaw> DSFOscillatorControls::RATIO_LAW()
{
	static auto res = make_shared<ctoot::control::IntegerLaw>(1, 9, "");
	return res;
}

weak_ptr<ctoot::control::IntegerLaw> DSFOscillatorControls::PARTIAL_LAW()
{
	static auto res = make_shared<ctoot::control::IntegerLaw>(1, 200, "");
	return res;
}

DSFOscillatorControls::DSFOscillatorControls(int32_t instanceIndex, std::string name, int32_t idOffset)
	: ctoot::control::CompoundControl(OscillatorIds::DSF_OSCILLATOR_ID, instanceIndex, name)
{
    this->idOffset = idOffset;
    createControls();
    deriveSampleRateIndependentVariables();
}

void DSFOscillatorControls::derive(ctoot::control::Control* c)
{
	switch (c->getId() - idOffset) {
	case RATIO_N:
		ratioNumerator = deriveRatioNumerator();
		break;
	case RATIO_D:
		ratioDenominator = deriveRatioDenominator();
		break;
	case PARTIALS:
		partialCount = derivePartialCount();
		break;
	case ROLLOFF:
		rolloffFactor = deriveRolloffFactor();
		rolloffInt = deriveRolloffInt();
		break;
	case WOLFRAM:
		canUseWolfram_ = deriveWolfram();
		break;
	}
}

void DSFOscillatorControls::createControls()
{
	auto rnc = createRatioControl(RATIO_N, "N");
	ratioNumeratorControl = rnc;
    add(std::move(rnc));

	auto rdc = createRatioControl(RATIO_D, "D");
	ratioDenominatorControl = rdc;
    add(std::move(rdc));
    
	auto pc = createPartialsControl(PARTIALS);
	partialsControl = pc;
	add(std::move(pc));

	auto roc = createRolloffControl(ROLLOFF);
	rolloffControl = roc;
    add(std::move(roc));
}

shared_ptr<ctoot::control::IntegerControl> DSFOscillatorControls::createRatioControl(int32_t id, std::string name)
{
    auto control = make_shared<ctoot::control::IntegerControl>(id + idOffset, name, RATIO_LAW(), 1.0f, 1);
    return control;
}

shared_ptr<ctoot::control::IntegerControl> DSFOscillatorControls::createPartialsControl(int32_t id)
{
    auto control = make_shared<ctoot::control::IntegerControl>(id + idOffset, "Partials", PARTIAL_LAW(), 1.0f, 10);
    return control;
}

shared_ptr<ctoot::control::FloatControl> DSFOscillatorControls::createRolloffControl(int32_t id)
{
    auto control = make_shared<ctoot::control::FloatControl>(id + idOffset, "Tone", ctoot::control::LinearLaw::UNITY(), 1.0f, 0.5f);
    return control;
}

shared_ptr<ctoot::control::BooleanControl> DSFOscillatorControls::createWolframControl(int32_t id)
{
    auto control = make_shared<ctoot::control::BooleanControl>(id, "W", false);
    return control;
}

void DSFOscillatorControls::deriveSampleRateIndependentVariables()
{
    ratioDenominator = deriveRatioDenominator();
    ratioNumerator = deriveRatioNumerator();
    partialCount = derivePartialCount();
    rolloffFactor = deriveRolloffFactor();
    canUseWolfram_ = deriveWolfram();
}

int32_t DSFOscillatorControls::deriveRatioDenominator()
{
    return ratioDenominatorControl.lock()->getUserValue();
}

int32_t DSFOscillatorControls::deriveRatioNumerator()
{
    return ratioNumeratorControl.lock()->getUserValue();
}

int32_t DSFOscillatorControls::derivePartialCount()
{
    return partialsControl.lock()->getUserValue();
}

float DSFOscillatorControls::deriveRolloffFactor()
{
    return rolloffControl.lock()->getValue() * 0.98f;
}

int32_t DSFOscillatorControls::deriveRolloffInt()
{
    return rolloffControl.lock()->getIntValue();
}

bool DSFOscillatorControls::deriveWolfram()
{
    if (!wolframControl.lock())
        return false;

    return wolframControl.lock()->getValue();
}

int32_t DSFOscillatorControls::getPartialCount()
{
    return partialCount;
}

float DSFOscillatorControls::getPartialRolloffFactor()
{
    return rolloffFactor;
}

int32_t DSFOscillatorControls::getPartialRolloffInt()
{
    return rolloffInt;
}

int32_t DSFOscillatorControls::getRatioDenominator()
{
    return ratioDenominator;
}

int32_t DSFOscillatorControls::getRatioNumerator()
{
    return ratioNumerator;
}

bool DSFOscillatorControls::canUseWolfram()
{
    return canUseWolfram_;
}
