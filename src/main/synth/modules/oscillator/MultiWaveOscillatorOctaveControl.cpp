#include <synth/modules/oscillator/MultiWaveOscillatorOctaveControl.hpp>

#include <synth/modules/oscillator/MultiWaveOscillatorControls.hpp>

using namespace ctoot::synth::modules::oscillator;
using namespace std;

MultiWaveOscillatorOctaveControl::MultiWaveOscillatorOctaveControl(int id, std::string name, nonstd::any value)
	: ctoot::control::EnumControl(id, name, value)
{
}

vector<nonstd::any> MultiWaveOscillatorOctaveControl::getValues()
{
	auto res = vector<nonstd::any>();
	for (auto& s : MultiWaveOscillatorControls::octaveArray)
		res.push_back(s);
	return res;
}
