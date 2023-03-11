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

            };

		}
	}
}
