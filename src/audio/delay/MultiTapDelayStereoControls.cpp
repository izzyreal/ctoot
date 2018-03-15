#include <audio/delay/MultiTapDelayStereoControls.hpp>

#include <audio/delay/DelayIds.hpp>
#include <audio/delay/MultiTapDelayControls.hpp>
#include <control/ControlColumn.hpp>
#include <control/Control.hpp>
#include <control/FloatControl.hpp>
#include <control/LogLaw.hpp>

using namespace ctoot::audio::delay;
using namespace ctoot::control;
using namespace std;

MultiTapDelayStereoControls::MultiTapDelayStereoControls()
	: MultiTapDelayStereoControls(3, 2000.0f)
{
}

weak_ptr<ControlLaw> MultiTapDelayStereoControls::DELAY_FACTOR_LAW() {
	static auto res = make_shared<LogLaw>(0.2f, 5.0f, "");
	return res;
}

MultiTapDelayStereoControls::MultiTapDelayStereoControls(int ntaps, float ms)
	: AbstractDelayControls(DelayIds::MULTI_TAP_DELAY_ID, "Stereo.Multi.Tap.Delay")
{
    msMax = ms;
    for (int a = 0; a < 2; a++) {
        auto name = (a == 0) ? "Left" : "Right";
        auto c = make_shared<MultiTapDelayControls>(a * 16, ntaps, msMax, name);
		perChannelControls.push_back(c);
		add(c);
    }

    auto delayFactorControlS = make_shared<FloatControl>(DELAY_FACTOR_ID, "Delay", DELAY_FACTOR_LAW(), 0.01f, 1.0f);
	delayFactorControl = delayFactorControlS;
    add(delayFactorControlS);
    derive(delayFactorControlS.get());
    add(createCommonControlColumn(false));
}

void MultiTapDelayStereoControls::derive(ctoot::control::Control* c)
{
    switch (c->getId()) {
    case DELAY_FACTOR_ID:
        delay = delayFactorControl.lock()->getValue();
        break;
    default:
        super::derive(c);
        break;
    }

}

float MultiTapDelayStereoControls::getMaxDelayMilliseconds()
{
    return msMax * int(5);
}

vector<weak_ptr<DelayTap>> MultiTapDelayStereoControls::getTaps(int chan)
{
    return perChannelControls[chan].lock()->getTaps();
}

int MultiTapDelayStereoControls::getChannelCount()
{
    return 2;
}

float MultiTapDelayStereoControls::getDelayFactor()
{
    return delay;
}

bool MultiTapDelayStereoControls::isBypassed()
{
    return AudioControls::isBypassed();
}

float MultiTapDelayStereoControls::getFeedback()
{
    return AbstractDelayControls::getFeedback();
}

float MultiTapDelayStereoControls::getMix()
{
    return AbstractDelayControls::getMix();
}
