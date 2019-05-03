#include "InverseRatioControl.hpp"

#include <audio/dynamics/DynamicsControlIds.hpp>
#include <audio/dynamics/DynamicsControls.hpp>

#include <cmath>

using namespace ctoot::audio::dynamics;
using namespace std;

InverseRatioControl::InverseRatioControl(DynamicsControls* dynamicsControls)
	: ctoot::control::FloatControl(DynamicsControlIds::RATIO + dynamicsControls->idOffset, "Ratio", DynamicsControls::INVERSE_RATIO_LAW(), 0.1f, 0.5f)
{
}

string InverseRatioControl::getValueString()
{
    //auto ratio = 1.0f / getValue();
    //auto dp = abs(ratio) >= 10.0f ? int32_t(0) : int32_t(1);
    //return format(("%1$." + dp +  "f", Float::valueOf(ratio))}));
	return "InverseRatioControl temp value str";
}

std::vector<std::string> InverseRatioControl::getPresetNames()
{
    return DynamicsControls::ratioPresets2;
}

void InverseRatioControl::applyPreset(string name)
{
	if (name.compare("Infinity") == 0) {
		setValue(0.0f);
		return;
	}
	setValue(1.0f / stoi(name));
}
