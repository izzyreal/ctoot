#include <synth/modules/oscillator/MultiWaveOscillatorOctaveControl.hpp>

#include <synth/modules/oscillator/MultiWaveOscillatorControls.hpp>

using namespace ctoot::synth::modules::oscillator;
using namespace std;

MultiWaveOscillatorOctaveControl::MultiWaveOscillatorOctaveControl(int id, std::string name, std::any value)
	: ctoot::control::EnumControl(id, name, value)
{
}

vector<std::any> MultiWaveOscillatorOctaveControl::getValues()
{
	auto res = vector<std::any>();
	for (auto& s : MultiWaveOscillatorControls::octaveArray)
		res.push_back(s);
	return res;
}
