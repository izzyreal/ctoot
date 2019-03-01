#include <synth/modules/oscillator/MultiWaveOscillatorWaveControl.hpp>

#include <synth/modules/oscillator/MultiWaveOscillatorControls.hpp>
#include <synth/modules/oscillator/MultiWaves.hpp>

using namespace ctoot::synth::modules::oscillator;
using namespace std;

MultiWaveOscillatorWaveControl::MultiWaveOscillatorWaveControl(int id, std::string name, std::any value)
	: ctoot::control::EnumControl(id, name, value)
{
}

vector<std::any> MultiWaveOscillatorWaveControl::getValues()
{
	auto res = vector<std::any>();
	for (auto& s : MultiWaves::getNames())
		res.push_back(s);
    return res;
}
