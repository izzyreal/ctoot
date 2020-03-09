#include "BusControls.hpp"

#include <audio/core/ChannelFormat.hpp>
#include <control/BooleanControl.hpp>

#include <stdio.h>

using namespace ctoot::audio::core;
using namespace ctoot::control;
using namespace ctoot::audio::mixer;
using namespace std;

BusControls::BusControls(int id, string name, weak_ptr<ChannelFormat> format)
	: AudioControls(id, name, -1)
{
	soloCount = 0;
	soloIndicator = new SoloIndicator();
	channelFormat = format.lock();
	auto mc = make_shared<ctoot::audio::meter::MeterControls>(format, "Meter");
	meterControls = mc;
	add(std::move(mc));
}

bool BusControls::hasSolo()
{
    return soloCount > 0;
}

weak_ptr<ChannelFormat> BusControls::getChannelFormat()
{
    return channelFormat;
}

void BusControls::update(moduru::observer::Observable* o, nonstd::any a)
{
	try {
		auto c = nonstd::any_cast<BooleanControl*>(a);
		if (c->getName().compare("Solo") == 0) {
			soloCount += c->getValue() ? 1 : -1;
			soloIndicator->setValue(hasSolo());
		}
	}
	catch (const std::exception& e) {
		//printf(e.what());
	}
}

bool BusControls::canBypass()
{
    return false;
}

string BusControls::toString()
{
	return getName() + " Bus";
}

SoloIndicator* BusControls::getSoloIndicator() {
	return soloIndicator;
}

weak_ptr<ctoot::audio::meter::MeterControls> BusControls::getMeterControls() {
	return meterControls;
}

BusControls::~BusControls() {
	if (soloIndicator != nullptr) {
		//delete soloIndicator; // is already deleted by ControlRow/CompoundControl
	}
}
