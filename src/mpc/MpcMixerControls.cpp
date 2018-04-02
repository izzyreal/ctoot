#include <mpc/MpcMixerControls.hpp>
#include <mpc/MpcFaderControl.hpp>
#include <audio/fader/FaderControl.hpp>
#include <audio/fader/FaderLaw.hpp>

using namespace ctoot::audio::fader;
using namespace ctoot::mpc;
using namespace std;

MpcMixerControls::MpcMixerControls(string name, float smoothingFactor) 
	: MixerControls(name, smoothingFactor)
{
}

FaderControl* MpcMixerControls::createFaderControl(bool muted)
{
    return new MpcFaderControl(muted);
}

MpcMixerControls::~MpcMixerControls() {
}
