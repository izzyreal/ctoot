#include <audio/delay/TempoDelayControls.hpp>

#include <audio/delay/DelayIds.hpp>
#include <audio/delay/DelayFactorControl.hpp>
#include <audio/delay/NamedFactor.hpp>
#include <control/ControlColumn.hpp>
#include <control/Control.hpp>
#include <control/FloatControl.hpp>

#define _USE_MATH_DEFINES
#include <math.h>  

using namespace ctoot::audio::delay;
using namespace ctoot::control;
using namespace std;

NamedFactor* TempoDelayControls::defaultFactor() {
	static auto res = new NamedFactor(1.0f, "1/4");
	return res;
}

std::vector<NamedFactor*> TempoDelayControls::factors() {
	static auto res = vector<NamedFactor*>{ new NamedFactor(0.25f, "1/16"), new NamedFactor(0.5f / int(3), "1/8T"), new NamedFactor(0.5f, "1/8"), new NamedFactor(1.0f / int(3), "1/4T"), defaultFactor(), new NamedFactor(2.0f / int(3), "1/2T"), new NamedFactor(2.0f, "1/2") };
	return res;
}

weak_ptr<LinearLaw> TempoDelayControls::DUCKING_LAW()
{
	static auto res = make_shared<LinearLaw>(int(0), int(20), "dB");
	return res;
}

weak_ptr<LogLaw> TempoDelayControls::CUTOFF_LAW()
{
	static auto res = make_shared<LogLaw>(int(200), int(20000), "Hz");
	return res;
}

constexpr int TempoDelayControls::DUCKING_ID;
constexpr int TempoDelayControls::LOWPASS_ID;

TempoDelayControls::TempoDelayControls()
	: AbstractDelayControls(DelayIds::TEMPO_DELAY_ID, "BPM.Delay")
{
	delayFactor = 0.75f;
	auto col = make_shared<ControlColumn>();
    col->add(make_shared<DelayFactorControl>(this));
    col->add((createFeedbackControl()));
    col->add((createMixControl()));
    add(col);
    auto col2 = make_shared<ControlColumn>();
	auto duckingControlS = createDuckingControl();
	duckingControl = duckingControlS;
    col2->add(duckingControlS);
	auto lowpassControlS = createLowpassControl();
	lowpassControl = lowpassControlS;
    col2->add(lowpassControlS);
    add(col2);
    derive(duckingControlS.get());
    derive(lowpassControlS.get());
}

static inline double log2lin(double dLogarithmic) {
	return pow(10.0, dLogarithmic * (1.0 / 20.0));
}

void TempoDelayControls::derive(Control* c)
{
	float freq;
	switch (c->getId()) {
	case DUCKING_ID:
		ducking = log2lin(-duckingControl.lock()->getValue());
		break;
	case LOWPASS_ID:
		freq = lowpassControl.lock()->getValue();
		lowpassCoeff = 1.0f - exp(-2.0 * M_PI * freq / 44100.0);
		break;
	default:
		super::derive(c);
		break;
	}
}

shared_ptr<FloatControl> TempoDelayControls::createDuckingControl()
{
    auto control = make_shared<FloatControl>(DUCKING_ID, "Ducking", DUCKING_LAW(), 0.01f, 0.0f);
    return control;
}

shared_ptr<FloatControl> TempoDelayControls::createLowpassControl()
{
    auto control = make_shared<FloatControl>(LOWPASS_ID, "Filter", CUTOFF_LAW(), 1.0f, 8000.0f);
    return control;
}

float TempoDelayControls::getDucking()
{
    return ducking;
}

float TempoDelayControls::getLowpassCoefficient()
{
    return lowpassCoeff;
}

float TempoDelayControls::getDelayFactor()
{
    return delayFactor;
}

float TempoDelayControls::getMaxDelayMilliseconds()
{
    return 2000;

}

bool TempoDelayControls::isBypassed()
{
    return AudioControls::isBypassed();
}

float TempoDelayControls::getFeedback()
{
    return AbstractDelayControls::getFeedback();
}

float TempoDelayControls::getMix()
{
    return AbstractDelayControls::getMix();
}
