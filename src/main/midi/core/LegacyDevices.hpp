#pragma once
#include <string>

namespace ctoot {
	namespace midi {
		namespace core {

			struct MidiDevice;
			class MidiSystem;

			class LegacyDevices
			{

			public:
				static void addDevice(std::string name, MidiSystem* system, bool input);
                //static void installPlatformComponents(java::sound::MidiSystem* system);

				LegacyDevices();

			};

		}
	}
}
