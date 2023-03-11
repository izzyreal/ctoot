#include "LegacyDevices.hpp"

#include "LegacyDeviceAdaptor.hpp"
#include "MidiSystem.hpp"

//#include <RtMidi.h>

using namespace ctoot::midi::core;
using namespace std;

LegacyDevices::LegacyDevices()
{
}

void LegacyDevices::addDevice(string name, MidiSystem* system, bool input)
{
	system->addMidiDevice(new LegacyDeviceAdaptor(name, input));
}

/*
void LegacyDevices::installPlatformComponents(MidiSystem* system)
{
    clinit();
    ::javax::sound::midi::MidiDevice* device = nullptr;
    auto infos = ::javax::sound::midi::MidiSystem::getMidiDeviceInfo();
    auto maxtx = 0;
    auto maxrx = 0;
    for (auto i = 0; i < npc(infos)->length; i++) {
        try {
            device = ::javax::sound::midi::MidiSystem::getMidiDevice((*infos)[i]);
            maxtx = npc(device)->getMaxTransmitters();
            maxrx = npc(device)->getMaxReceivers();
            if(maxtx == 0 || maxrx == 0)
                continue;

            addDevice(device, system);
        } catch (::javax::sound::midi::MidiUnavailableException* e) {
//            npc(::java::lang::System::out())->println(stringBuilder().append(npc((*infos)[i])->getName())->append(" Unavailable!"->toString());
        }
    }
}
*/