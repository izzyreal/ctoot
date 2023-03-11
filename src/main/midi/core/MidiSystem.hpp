#pragma once

#include <observer/Observable.hpp>

namespace ctoot::midi::core {

    struct MidiDevice;
    struct MidiInput;
    struct MidiOutput;

    class MidiSystem
            : public moduru::observer::Observable
    {
    public:
        virtual void addMidiDevice(MidiDevice *device) = 0;

        virtual void removeMidiDevice(MidiDevice *device) = 0;

        virtual std::vector<MidiInput *> getMidiInputs() = 0;

        virtual std::vector<MidiOutput *> getMidiOutputs() = 0;

        virtual void close() = 0;
    };

}
