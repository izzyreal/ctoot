#include <audio/delay/WowFlutterControls.hpp>

#include <audio/delay/DelayIds.hpp>
#include <control/ControlColumn.hpp>
#include <control/Control.hpp>
#include <control/LinearLaw.hpp>

#define _USE_MATH_DEFINES
#include <math.h>  

using namespace ctoot::audio::delay;
using namespace ctoot::audio;
using namespace ctoot::control;
using namespace std;

constexpr int WowFlutterControls::SPEED;
constexpr int WowFlutterControls::LEVEL;

vector<float> WowFlutterControls::diameters() {
	static vector<float> res{ 9.06f, 26.0f, 16.0f, 18.0f, 9.75f, 37.8f, 1.292f };
	return res;
}

vector<string> WowFlutterControls::speeds() {
	static vector<string> res{ "3.75", "7.5", "15", "30" };
	return res;
}

WowFlutterControls::WowFlutterControls()
	: AudioControls(DelayIds::WOW_FLUTTER_ID, "Wow")
{
	auto col = make_shared<ControlColumn>();
	auto speedControlS = make_shared<TapeSpeedControl>(this);
	speedControl = speedControlS;
    col->add(speedControlS);
    derive(speedControlS.get());
	auto levelControlS = createLevelControl();
	levelControl = levelControlS;
    col->add(levelControlS);
	derive(levelControlS.get());
    add(col);
}

void WowFlutterControls::derive(Control* c)
{
	float ips;
	switch (c->getId()) {
	case SPEED: {
		auto s = speedControl.lock()->getValueString();
		ips = stof(s);
		speedChanged(ips);
		break;
	}
	case LEVEL:
		level = levelControl.lock()->getValue();
		break;
	default:
		break;
	}
}

shared_ptr<FloatControl> WowFlutterControls::createLevelControl()
{
    auto control = make_shared<FloatControl>(LEVEL, "Level", LinearLaw::UNITY(), 0.1f, 0.1f);
    return control;
}

void WowFlutterControls::speedChanged(float ips)
{
	auto mmps = 25.4f * ips;
	auto mm = diameters();
	auto n = mm.size();
	nextFreqs = vector<float>(n);
	nextAmps = vector<float>(n);
	for (auto i = int(0); i < n; i++) {
		nextFreqs[i] = mmps / static_cast<float>((M_PI * mm[i]));
		nextAmps[i] = 0.8f / (nextFreqs[i] * n);
	}
	frequencies = nextFreqs;
	fuid += 1;
}

float WowFlutterControls::getLevel()
{
    return level;
}

vector<float> WowFlutterControls::getAmplitudes()
{
    return amplitudes;
}

int WowFlutterControls::getFrequencyUid()
{
    amplitudes = nextAmps;
    return fuid;
}

vector<float> WowFlutterControls::getFrequencies()
{
    return frequencies;
}

float WowFlutterControls::getMaxDelayMilliseconds()
{
    return 10.0f;
}

bool WowFlutterControls::isBypassed()
{
    return AudioControls::isBypassed();
}
