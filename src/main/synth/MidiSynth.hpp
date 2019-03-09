#pragma once
#include <midi/core/MidiDevice.hpp>
#include <midi/core/MidiInput.hpp>
#include <audio/system/AudioDevice.hpp>

namespace ctoot {
	namespace synth {

		class MidiSynth
			: public virtual ctoot::midi::core::MidiDevice
			, public virtual ctoot::midi::core::MidiInput
			, public virtual ctoot::audio::system::AudioDevice
		{
		public:
			virtual void setLocation(std::string location) = 0;
			virtual std::string getName() = 0;
		};

	}
}
