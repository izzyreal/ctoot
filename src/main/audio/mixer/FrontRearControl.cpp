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

void FrontRearControl::setValue(float value)
{
	front = static_cast<float>(cos(M_PI / 2 * value));
	rear = static_cast<float>(sin(M_PI / 2 * value));
	FloatControl::setValue(value);
}

