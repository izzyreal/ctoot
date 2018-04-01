#include <synth/modules/oscillator/MultiWaveOscillatorWidthControl.hpp>

#include <synth/modules/oscillator/MultiWaveOscillatorControls.hpp>

using namespace ctoot::synth::modules::oscillator;
using namespace std;

MultiWaveOscillatorWidthControl::MultiWaveOscillatorWidthControl(int id, std::string name, std::weak_ptr<ctoot::control::ControlLaw> law, float precision, float initialValue)
	: ctoot::control::FloatControl(id, name, law, precision, initialValue)
{
}

vector<string> MultiWaveOscillatorWidthControl::getPresetNames()
{
    return presetNames;
}

void MultiWaveOscillatorWidthControl::applyPreset(string presetName)
{
	if (presetName.compare("50%") == 0) {
		setValue(0.5f);
	}
}
