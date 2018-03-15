#include <audio/delay/ModulatedDelayControls.hpp>

#include <audio/delay/DelayIds.hpp>
#include <audio/delay/ShapeControl.hpp>
#include <control/BooleanControl.hpp>
#include <control/ControlColumn.hpp>
#include <control/Control.hpp>
#include <control/FloatControl.hpp>
#include <control/LinearLaw.hpp>
#include <control/LogLaw.hpp>

using namespace ctoot::audio::delay;
using namespace ctoot::control;
using namespace std;

constexpr float ModulatedDelayControls::HALF_ROOT_2;

weak_ptr<ControlLaw> ModulatedDelayControls::DELAY_LAW()
{
	static auto res = make_shared<LogLaw>(0.1f, 25.0f, "ms");
	return res;
}

weak_ptr<ControlLaw> ModulatedDelayControls::RATE_LAW()
{
	static auto res = make_shared<LogLaw>(0.02f, 7.0f, "Hz");
	return res;
}

constexpr int ModulatedDelayControls::DRY_ID;
constexpr int ModulatedDelayControls::DELAY_ID;
constexpr int ModulatedDelayControls::RATE_ID;
constexpr int ModulatedDelayControls::SHAPE_ID;
constexpr int ModulatedDelayControls::DEPTH_ID;
constexpr int ModulatedDelayControls::PHASE_ID;

ModulatedDelayControls::ModulatedDelayControls()
	: ModulatedDelayControls(DelayIds::MODULATED_DELAY_ID, "Modulated.Delay")
{
}

ModulatedDelayControls::ModulatedDelayControls(int id, std::string name)
	: AbstractDelayControls(id, name)
{
    add(createControlColumn1());
	auto shapeControlS = make_shared<ShapeControl>(SHAPE_ID);
	shapeControl = shapeControlS;
	auto rateControlS = make_shared<FloatControl>(RATE_ID, "Rate", RATE_LAW(), 0.01f, 0.2f);
	rateControl = rateControlS;
    auto depthControlS = make_shared<FloatControl>(DEPTH_ID, "Depth", LinearLaw::UNITY(), 0.01f, 0.5f);
	depthControl = depthControlS;
    auto g2 = make_shared<ControlColumn>();
    g2->add(shapeControlS);
    g2->add(rateControlS);
    g2->add(depthControlS);
    add(g2);

    derive(shapeControlS.get());
    derive(rateControlS.get());
    derive(depthControlS.get());
    
	auto g3 = make_shared<ControlColumn>();
    g3->add(createFeedbackInvertControl());
    g3->add(createFeedbackControl());

	auto wetControlS = make_shared<FloatControl>(MIX_ID, "Wet", LinearLaw::UNITY(), 0.1f, HALF_ROOT_2);
	wetControl = wetControlS;
    g3->add(wetControlS);
    add(g3);
    derive(wetControlS.get());
}

void ModulatedDelayControls::derive(Control* c)
{
	switch (c->getId()) {
	case DRY_ID:
		dry = dryControl.lock()->getValue();
		break;
	case DELAY_ID:
		delay = delayControl.lock()->getValue();
		break;
	case MIX_ID:
		wet = wetControl.lock()->getValue();
		break;
	case RATE_ID:
		rate = rateControl.lock()->getValue();
		break;
	case DEPTH_ID:
		depth = depthControl.lock()->getValue();
		break;
	case SHAPE_ID:
		shape = shapeControl.lock()->getIntValue();
		break;
	case PHASE_ID:
		quadrature = phaseControl.lock()->getValue();
		break;
	default:
		super::derive(c);
		break;
	}
}

shared_ptr<ControlColumn> ModulatedDelayControls::createControlColumn1()
{
    auto phaseControlS = make_shared<BooleanControl>(PHASE_ID, "PQ", false);
	phaseControl = phaseControlS;
    auto delayControlS = make_shared<FloatControl>(DELAY_ID, "Delay", DELAY_LAW(), 0.1f, 2.0f);
	delayControl = delayControlS;
    auto dryControlS = make_shared<FloatControl>(DRY_ID, "Dry", LinearLaw::UNITY(), 0.1f, HALF_ROOT_2);
	dryControl = dryControlS;
    auto g1 = make_shared<ControlColumn>();
    g1->add(phaseControlS);
    g1->add(delayControlS);
    g1->add(dryControlS);
    derive(phaseControlS.get());
    derive(delayControlS.get());
    derive(dryControlS.get());
    return g1;
}

float ModulatedDelayControls::getMaxDelayMilliseconds()
{
    return 60.0f;
}

float ModulatedDelayControls::getDelayMilliseconds()
{
    return delay;
}

float ModulatedDelayControls::getRate()
{
    return rate;
}

float ModulatedDelayControls::getDepth()
{
    return depth;
}

float ModulatedDelayControls::getDry()
{
    return dry;
}

float ModulatedDelayControls::getWet()
{
    return wet;
}

int ModulatedDelayControls::getLFOShape()
{
    return shape;
}

bool ModulatedDelayControls::isPhaseQuadrature()
{
    return quadrature;
}

bool ModulatedDelayControls::isBypassed()
{
    return AudioControls::isBypassed();
}

float ModulatedDelayControls::getFeedback()
{
    return AbstractDelayControls::getFeedback();
}
