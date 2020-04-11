#include <audio/core/AudioControls.hpp>
#include <control/BypassControl.hpp>

using namespace ctoot::audio::core;
using namespace ctoot::control;
using namespace std;

AudioControls::AudioControls(int id, string name) : AudioControls(id, name, 127) {
}

AudioControls::AudioControls(int id, string name, int bypassId) : CompoundControl(id, name)
{
	if (bypassId != -1) {
		auto bpc = make_shared<BypassControl>(bypassId);
		add(bpc);
		bypassControl = bpc;

	}
}

bool AudioControls::hasOrderedFrequencies()
{
    return false;
}

bool AudioControls::canBeMinimized()
{
    return true;
}

bool AudioControls::canBypass()
{
    return true;
}

void AudioControls::setBypassed(bool state)
{
	if (canBypass() && bypassControl.lock()) {
		bypassControl.lock()->setValue(state);
	}
}

bool AudioControls::isBypassed()
{
    if (!bypassControl.lock()) return false;
    return bypassControl.lock()->getValue();
}

ctoot::control::BooleanControl* AudioControls::getBypassControl()
{
    return bypassControl.lock().get();
}

string AudioControls::getPersistenceDomain()
{
	return "audio";
}

AudioControls::~AudioControls() {
}
