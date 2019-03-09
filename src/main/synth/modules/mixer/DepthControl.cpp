#include <synth/modules/mixer/DepthControl.hpp>

using namespace ctoot::synth::modules::mixer;
using namespace std;

DepthControl::DepthControl(int id, std::string name, std::weak_ptr<ctoot::control::ControlLaw> law, float precision, float initialValue)
	: ctoot::control::FloatControl(id, name, law, precision, initialValue)
{
}

vector<string> DepthControl::getPresetNames()
{
    return presetNames;
}

void DepthControl::applyPreset(string presetName)
{
	if (presetName.compare("Off") == 0) {
		setValue(0.0f);
	}
}
