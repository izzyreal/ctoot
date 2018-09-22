#include "MidiPersistence.hpp"

//#include <javax/sound/midi/InvalidMidiDataException.hpp>
#include <thirdp/midifile/MidiFile.h>
#include <thirdp/midifile/MidiEvent.h>
#include <midi/core/MidiMessage.hpp>
#include <control/CompoundControl.hpp>
#include <control/Control.hpp>
#include <control/automation/ControlSysexMsg.hpp>

using namespace ctoot::control::automation;
using namespace ctoot::control;
using namespace std;

MidiPersistence::MidiPersistence() 
{
}
int MidiPersistence::eventCounter = 0;

void MidiPersistence::store(int32_t providerId, int32_t moduleId, int32_t instanceIndex, std::weak_ptr<CompoundControl> parent, smf::MidiFile& midiFile)
{
	for (auto& c : parent.lock()->getControls()) {
		auto cc = dynamic_pointer_cast<CompoundControl>(c.lock());
		if (cc) {
			store(providerId, moduleId, instanceIndex, cc, midiFile);
		}
		else {
			auto cl = c.lock();
			auto id = cl->getId();
			if (!cl->isIndicator() && id >= 0 && id < 128) {
				//MLOG("Storing event " + to_string(eventCounter) + " for control " + cl->getName() + " intValue " + to_string(cl->getIntValue()) + " id " + to_string(id));
				auto msg = ControlSysexMsg::createControl(providerId, moduleId, instanceIndex, id, cl->getIntValue());
				smf::MidiEvent me;
				me.setMessage(msg);
				midiFile.addEvent(0, 0, me);
				eventCounter++;
			}
		}
	}
}

