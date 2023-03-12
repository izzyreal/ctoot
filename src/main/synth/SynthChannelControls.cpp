#include <synth/SynthChannelControls.hpp>
#include <control/Control.hpp>
#include <control/ControlLaw.hpp>
#include <synth/ControlChange.hpp>

using namespace ctoot::synth;
using namespace ctoot::control;
using namespace std;

SynthChannelControls::SynthChannelControls(int id, string name)
	: CompoundControl(id, name)
{
}

void SynthChannelControls::close()
{
}
