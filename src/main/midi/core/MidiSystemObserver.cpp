#include <midi/core/MidiSystemObserver.hpp>

#include <midi/core/DefaultMidiSystem.hpp>

using namespace ctoot::midi::core;

MidiSystemObserver::MidiSystemObserver(DefaultMidiSystem *dms)
	: dms(dms)
{
}

void MidiSystemObserver::update(moduru::observer::Observable* o, nonstd::any a)
{
	dms->notifyObservers();
}

MidiSystemObserver::~MidiSystemObserver() {
	dms = nullptr;
}
