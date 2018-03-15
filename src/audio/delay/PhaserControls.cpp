#include <audio/delay/PhaserControls.hpp>

#include <audio/delay/DelayIds.hpp>
#include <audio/delay/StagesControl.hpp>
#include <control/ControlColumn.hpp>
#include <control/Control.hpp>
#include <control/LinearLaw.hpp>
#include <control/LogLaw.hpp>

using namespace ctoot::audio::delay;
using namespace ctoot::audio::core;
using namespace ctoot::control;
using namespace std;

constexpr int PhaserControls::RATE_ID;
constexpr int PhaserControls::DEPTH_ID;
constexpr int PhaserControls::FEEDBACK_ID;
constexpr int PhaserControls::STAGES_ID;

PhaserControls::PhaserControls()
	: AudioControls(DelayIds::PHASER_ID, "Phaser")
{
	auto cc =  make_shared<ControlColumn>();
	auto stagesControlS = make_shared<StagesControl>(stages);
	stagesControl = stagesControlS;
	cc->add(stagesControlS);
	
	auto rateControlS = createRateControl();
	rateControl = rateControlS;
    cc->add(rateControlS);
	
	auto depthControlS = createDepthControl();
	depthControl = depthControlS;
	cc->add(depthControlS);
    
	auto feedbackControlS = createFeedbackControl();
	feedbackControl = feedbackControlS;
	cc->add(feedbackControlS);
    add(cc);
    derive(rateControlS.get());
    derive(depthControlS.get());
    derive(feedbackControlS.get());
    derive(stagesControlS.get());
}

void PhaserControls::derive(Control* c)
{
	switch (c->getId()) {
	case RATE_ID:
		rate = rateControl.lock()->getValue();
		break;
	case DEPTH_ID:
		depth = depthControl.lock()->getValue();
		break;
	case FEEDBACK_ID:
		feedback = feedbackControl.lock()->getValue();
		break;
	case STAGES_ID:
		stages = stagesControl.lock()->getStages();
		break;
	}
}

weak_ptr<ControlLaw> PhaserControls::RATE_LAW() {
	static auto res = make_shared<LogLaw>(0.1f, 2.0f, "Hz");
	return res;
}

shared_ptr<FloatControl> PhaserControls::createRateControl()
{
    return make_shared<FloatControl>(RATE_ID, "Rate", RATE_LAW(), 0.01f, 0.5f);
}

shared_ptr<FloatControl> PhaserControls::createDepthControl()
{
    return make_shared<FloatControl>(DEPTH_ID, "Depth", LinearLaw::UNITY(), 0.01f, 1.0f);
}

shared_ptr<FloatControl> PhaserControls::createFeedbackControl()
{
    return make_shared<FloatControl>(FEEDBACK_ID, "Resonance", LinearLaw::UNITY(), 0.01f, 0.0f);
}

float PhaserControls::getDepth()
{
    return depth;
}

float PhaserControls::getFeedback()
{
    return feedback;
}

float PhaserControls::getRate()
{
    return rate;
}

int PhaserControls::getStages()
{
    return stages;
}

bool PhaserControls::isBypassed()
{
    return AudioControls::isBypassed();
}
