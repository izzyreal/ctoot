#include <midi/message/PitchMsg.hpp>
#include <midi/core/MidiMessage.hpp>

using namespace ctoot::midi::message;

PitchMsg::PitchMsg()
{
}

ctoot::midi::core::MidiMessage* PitchMsg::transpose(ctoot::midi::core::MidiMessage* msg, int semitones)
{
	auto note = getData1(msg) + semitones;
	if (note > 127) note = 127;
	else if (note < 0) note = 0;
	return setData1(msg, note);
}

int PitchMsg::getPitch(ctoot::midi::core::MidiMessage* msg)
{
	return getData1(msg);
}

