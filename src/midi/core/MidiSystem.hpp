#pragma once
//#include <misc/IObservable.hpp>
#include <observer/Observable.hpp>

namespace ctoot {
	namespace midi {
		namespace core {

			class MidiDevice;
			class MidiInput;
			class MidiOutput;

			class MidiSystem
				: public moduru::observer::Observable
			{
			public:
				virtual void addMidiDevice(MidiDevice* device) = 0;
				virtual void removeMidiDevice(MidiDevice* device) = 0;
				virtual std::vector<MidiDevice*> getMidiDevices() = 0;
				virtual std::vector<MidiInput*> getMidiInputs() = 0;
				virtual std::vector<MidiOutput*> getMidiOutputs() = 0;
				virtual void close() = 0;
			};

		}
	}
}
