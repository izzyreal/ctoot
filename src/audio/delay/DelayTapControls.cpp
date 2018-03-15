#include <audio/delay/DelayTapControls.hpp>

#include <control/ControlLaw.hpp>
#include <control/LinearLaw.hpp>

using namespace ctoot::audio::delay;
using namespace ctoot::control;
using namespace std;

DelayTapControls::DelayTapControls(int id, weak_ptr<ControlLaw> law)
	: CompoundControl(id, "")
{

	auto delayControlS = make_shared<FloatControl>(id, "Delay", law, 0.1f, law.lock()->getMaximum() / 4);
	delayControl = delayControlS;
    add(delayControlS);

	auto levelControlS = make_shared<FloatControl>(id + int(1), "Level", ctoot::control::LinearLaw::UNITY(), 0.01f, 0.0f);
	levelControl = levelControlS;
    add(levelControlS);
}

bool DelayTapControls::isAlwaysVertical()
{
    return true;
}

float DelayTapControls::getDelayMilliseconds()
{
    return delayControl.lock()->getValue();
}

float DelayTapControls::getLevel()
{
    return levelControl.lock()->getValue();
}
