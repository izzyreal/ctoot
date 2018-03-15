#include <audio/delay/DelayMixControl.hpp>

#include <audio/delay/AbstractDelayControls.hpp>
#include <control/LinearLaw.hpp>

using namespace ctoot::audio::delay;
using namespace ctoot::control;
using namespace std;

vector<string> DelayMixControl::presetNames{ "Dry", "Wet" };

DelayMixControl::DelayMixControl()
	: FloatControl(AbstractDelayControls::MIX_ID, "Mix", ctoot::control::LinearLaw::UNITY(), 0.01f, 0.5f)
{
}

vector<string> ctoot::audio::delay::DelayMixControl::getPresetNames()
{
    return presetNames;
}

void ctoot::audio::delay::DelayMixControl::applyPreset(std::string name)
{
	if (name.compare("Dry") == 0) {
		setValue(0.0f);
	}
	else if (name.compare("Wet") == 0) {
		setValue(1.0f);
	}
}
