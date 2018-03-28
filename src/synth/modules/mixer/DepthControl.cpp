#include <synth/modules/mixer/DepthControl.hpp>

using namespace ctoot::synth::modules::mixer;

std::vector<std::string> DepthControl::getPresetNames()
{
    return presetNames;
}

void DepthControl::applyPreset(std::string presetName)
{
	if (presetName.compare("Off") == 0) {
		setValue(0.0f);
	}
}
