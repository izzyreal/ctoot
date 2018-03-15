#include <audio/delay/AbstractDelayControls.hpp>

#include <audio/delay/DelayMixControl.hpp>
#include <control/BooleanControl.hpp>
#include <control/ControlColumn.hpp>
#include <control/Control.hpp>
#include <control/FloatControl.hpp>
#include <control/LinearLaw.hpp>

constexpr int ctoot::audio::delay::AbstractDelayControls::FEEDBACK_INVERT_ID;
constexpr int ctoot::audio::delay::AbstractDelayControls::FEEDBACK_ID;
constexpr int ctoot::audio::delay::AbstractDelayControls::MIX_ID;
constexpr int ctoot::audio::delay::AbstractDelayControls::DELAY_FACTOR_ID;

using namespace ctoot::audio::delay;
using namespace ctoot::audio::core;
using namespace ctoot::control;
using namespace std;

AbstractDelayControls::AbstractDelayControls(int id, std::string name)
	: AudioControls(id, name)
{
}

void ctoot::audio::delay::AbstractDelayControls::derive(ctoot::control::Control* c)
{
    switch (c->getId()) {
    case FEEDBACK_INVERT_ID:
    case FEEDBACK_ID:
        feedback = isFeedbackInverted() ? -feedbackControl.lock()->getValue() : feedbackControl.lock()->getValue();
        break;
    case MIX_ID:
        mix = mixControl.lock()->getValue();
        break;
    case DELAY_FACTOR_ID:
        break;
    }
}

bool ctoot::audio::delay::AbstractDelayControls::isFeedbackInverted()
{
	if (!feedbackInvertControl.lock())
		return false;

	return feedbackInvertControl.lock()->getValue();
}

shared_ptr<BooleanControl> ctoot::audio::delay::AbstractDelayControls::createFeedbackInvertControl()
{
    auto res = make_shared<BooleanControl>(FEEDBACK_INVERT_ID, "Invert", false);
	feedbackInvertControl = res;
    return res;
}

shared_ptr<FloatControl> ctoot::audio::delay::AbstractDelayControls::createFeedbackControl()
{
    auto res = make_shared<FloatControl>(FEEDBACK_ID, "Resonance", ctoot::control::LinearLaw::UNITY(), 0.01f, 0.5f);
	feedbackControl = res;
	derive(res.get());
    return res;
}

shared_ptr<FloatControl> ctoot::audio::delay::AbstractDelayControls::createMixControl()
{
    auto res = make_shared<DelayMixControl>();
	mixControl = res;
    return res;
}

shared_ptr<ControlColumn> ctoot::audio::delay::AbstractDelayControls::createCommonControlColumn(bool withInverts)
{
	auto g = make_shared<ControlColumn>();
	if (withInverts)
		g->add(createFeedbackInvertControl());

	g->add(createFeedbackControl());
	g->add(createMixControl());
	return g;
}

float ctoot::audio::delay::AbstractDelayControls::getFeedback()
{
    return feedback;
}

float ctoot::audio::delay::AbstractDelayControls::getMix()
{
    return mix;
}
