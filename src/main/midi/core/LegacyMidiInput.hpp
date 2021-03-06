#pragma once

#include <midi/core/MidiInput.hpp>

#include <string>

namespace ctoot {
	namespace midi {
		namespace core {

			class MidiMessage;
			struct MidiDevice;
			class LegacyDeviceAdaptor;

			class LegacyMidiInput
				: public virtual MidiInput
			{

			private:
//                RtMidiOut* receiver;
				std::string name;

			public:
				void transport(ctoot::midi::core::MidiMessage* message, int timestamp) override;
				virtual void closeInput();
				virtual int getLatency();
				std::string getName() override;

				LegacyMidiInput(LegacyDeviceAdaptor* adaptor, std::string name);
			

			public:
				LegacyDeviceAdaptor* adaptor;

			private:
				//friend class LegacyDevices;
				//friend class LegacyDeviceAdaptor;
				//friend class LegacyMidiOutput;
				//friend class LegacyMidiOutput_DeviceMidiOutput_1;
			};

		}
	}
}
