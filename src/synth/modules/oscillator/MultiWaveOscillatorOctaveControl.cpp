#include <synth/modules/oscillator/MultiWaveOscillatorOctaveControl.hpp>

#include <synth/modules/oscillator/MultiWaveOscillatorControls.hpp>

using namespace ctoot::synth::modules::oscillator;
using namespace std;

MultiWaveOscillatorOctaveControl::MultiWaveOscillatorOctaveControl(int id, std::string name, boost::any value)
	: ctoot::control::EnumControl(id, name, value)
{
}

vector<boost::any> MultiWaveOscillatorOctaveControl::getValues()
{
	auto res = vector<boost::any>();
	for (auto& s : MultiWaveOscillatorControls::octaveArray)
		res.push_back(s);
	return res;
}
