#include <synth/modules/oscillator/MultiWaveOscillatorDetuneControl.hpp>

#include <synth/modules/oscillator/MultiWaveOscillatorControls.hpp>

using namespace ctoot::synth::modules::oscillator;
using namespace std;

MultiWaveOscillatorDetuneControl::MultiWaveOscillatorDetuneControl(int id, std::string name, std::weak_ptr<ctoot::control::ControlLaw> law, float precision, float initialValue)
	: ctoot::control::FloatControl(id, name, law, precision, initialValue)
{
}

vector<string> MultiWaveOscillatorDetuneControl::getPresetNames()
{
    return presetNames;
}

void MultiWaveOscillatorDetuneControl::applyPreset(string presetName)
{
	if (presetName.compare("Off") == 0) {
		setValue(0.0f);
	}
}
