#include "FrontRearControl.hpp"

#include <audio/mixer/MixControlIds.hpp>
#include <audio/mixer/MixControls.hpp>
#include <control/LinearLaw.hpp>

using namespace ctoot::audio::mixer;
using namespace std;

FrontRearControl::FrontRearControl() 
	: FloatControl(MixControlIds::FRONT_SURROUND, "F.S", ctoot::control::LinearLaw::UNITY(), 0.01f, 0.5f)
{
	front = MixControls::HALF_ROOT_TWO();
	rear = MixControls::HALF_ROOT_TWO();
}

float FrontRearControl::getFront()
{
    return front;
}

float FrontRearControl::getRear()
{
    return rear;
}

void FrontRearControl::setValue(float value)
{
	front = static_cast<float>(cos(M_PI / 2 * value));
	rear = static_cast<float>(sin(M_PI / 2 * value));
	FloatControl::setValue(value);
}

vector<string> FrontRearControl::getPresetNames()
{
	static vector<string> res { "Front", "Middle", "Rear" };
	return res;
}

void FrontRearControl::applyPreset(string presetName)
{
	if (presetName.compare("Middle") == 0) {
		setValue(0.5f);
	}
	else if (presetName.compare("Front") == 0) {
		setValue(0.0f);
	}
	else if (presetName.compare("Rear") == 0) {
		setValue(1.0f);
	}
}
