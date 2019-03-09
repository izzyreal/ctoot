#include <audio/basic/tap/TapControls.hpp>

#include <audio/basic/BasicIds.hpp>
#include <audio/core/AudioBuffer.hpp>
#include <audio/core/Taps.hpp>
#include <control/BooleanControl.hpp>
#include <control/CompoundControl.hpp>

#include <stdexcept>

using namespace ctoot::audio::basic::tap;
using namespace ctoot::audio::core;
using namespace std;

TapControls::TapControls()
	: AudioControls(ctoot::audio::basic::BasicIds::TAP, "Tap")
{
    getBypassControl()->setValue(false);
    getBypassControl()->setEnabled(false);
}

void TapControls::setParent(ctoot::control::CompoundControl* parent)
{
	AudioControls::setParent(parent);
	if (parent != nullptr) {
		buffer = Taps::create(this);
	}
	else {
		removeBuffer();
	}
}

void TapControls::removeBuffer()
{
	if (buffer == nullptr)
		return;

	Taps::remove(buffer);
	buffer = nullptr;
}

ctoot::audio::core::AudioBuffer* TapControls::getBuffer()
{
    return buffer;
}

void TapControls::reference(int32_t ref)
{
	if (ref != 1 && ref != -int32_t(1)) {
		throw std::invalid_argument("argument must be +/- 1");
	}
	refCount += ref;
	if (refCount < 0) {
		refCount = 0;
		string errormsg = "refCount < 0";
		printf(errormsg.c_str());
	}
}

bool TapControls::canBeDeleted()
{
    return isInactive();
}

bool TapControls::isInactive()
{
    return refCount == 0;
}
