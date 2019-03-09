#pragma once
#include <midi/core/MidiSystem.hpp>

#include <string>
#include <vector>

namespace ctoot {
	namespace midi {
		namespace core {

			struct MidiOutput;
			struct MidiInput;
			class MidiConnection;

			class ConnectedMidiSystem
				: public virtual MidiSystem
			{
			public:
				virtual void createMidiConnection(MidiOutput* from, MidiInput* to, int flags) = 0;
				virtual void closeMidiConnection(MidiOutput* from, MidiInput* to) = 0;
				virtual void createMidiConnection(std::string* fromPortName, std::string* toPortName, int flags) = 0;
				virtual void closeMidiConnection(std::string* fromPortName, std::string* toPortName) = 0;
				virtual std::vector<MidiConnection*> getMidiConnections() = 0;

			};

		}
	}
}
