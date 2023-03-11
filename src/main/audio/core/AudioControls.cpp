#include <audio/core/AudioControls.hpp>
#include <control/BypassControl.hpp>

using namespace ctoot::audio::core;
using namespace ctoot::control;
using namespace std;

AudioControls::AudioControls(int id, string name) : AudioControls(id, name, 127) {
}

AudioControls::AudioControls(int id, string name, int bypassId) : CompoundControl(id, name)
{
}
