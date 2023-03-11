#include <midi/core/MidiConnection.hpp>

#include <midi/core/MidiInput.hpp>
#include <midi/core/MidiOutput.hpp>

using namespace ctoot::midi::core;

MidiConnection::MidiConnection(MidiOutput* from, MidiInput* to, int flags) 
{
	flags = 0;
	if (from == nullptr || to == nullptr) {
		//        throw new ::java::lang::IllegalArgumentException("MidiConnection constructor null argument";
	}
	this->from = from;
	this->to = to;
	this->flags = flags;
	from->addConnectionTo(to);
}

const int MidiConnection::PLAYBACK;
const int MidiConnection::SYSTEM;
const int MidiConnection::OUTPUT_LOCKED;
const int MidiConnection::INPUT_LOCKED;

void MidiConnection::close()
{
    from->removeConnectionTo(to);
    //from = nullptr;
    //to = nullptr;
}

MidiOutput* MidiConnection::getMidiOutput()
{
    return from;
}

MidiInput* MidiConnection::getMidiInput()
{
    return to;
}

MidiConnection::~MidiConnection() {
	//delete from;
	//from = nullptr;
	//delete to;
	//to = nullptr;
}
