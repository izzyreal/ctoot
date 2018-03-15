#include "FaderControl.hpp"

#include <audio/fader/FaderLaw.hpp>

using namespace std;
using namespace ctoot::audio::fader;

FaderControl::FaderControl(int id, weak_ptr<ctoot::control::ControlLaw> law, float initialValue) 
	: LawControl(id, "Level", law, 0.1f, initialValue)
{
}

float FaderControl::getGain()
{
    return gain;
}
weak_ptr<FaderLaw> FaderControl::SEMI_LOG()
{
	static shared_ptr<FaderLaw> res = make_shared<FaderLaw>(1024, -10.0f, 10.0f, 0.33f);
	return res;
}

weak_ptr<FaderLaw> FaderControl::LOG()
{
	static shared_ptr<FaderLaw> res = make_shared<FaderLaw>(1024, -20.0f, 15.0f, 0.2f);
	return res;
}

weak_ptr<FaderLaw> FaderControl::BROADCAST()
{
	static shared_ptr<FaderLaw> res = make_shared<FaderLaw>(1024, -30.0f, 15.0f, 0.125f);
	return res;
}

float FaderControl::ATTENUATION_CUTOFF()
{
	return 100.0f;
}

weak_ptr<FaderLaw> FaderControl::defaultLaw()
{
	return FaderControl::BROADCAST();
}

FaderControl::~FaderControl() {

}
