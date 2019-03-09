#pragma once

#include <vector>
#include <string>

#include <memory>

namespace ctoot {

	namespace midi {
		namespace core {
			class MidiSystem;
		}
	}
	namespace audio {
		namespace system {
			class AudioSystem;
		}
	}


	namespace synth {

		class MidiSynth;
		class SynthRackControls;
		class SynthRackObserver;

		class SynthRack
		{

		private:
			std::weak_ptr<ctoot::midi::core::MidiSystem> midiSystem{ };
			std::weak_ptr<ctoot::audio::system::AudioSystem> audioSystem{};
			std::vector<std::shared_ptr<MidiSynth>> synths{};
			ctoot::synth::SynthRackObserver* observer{ nullptr };

		public:
			virtual void setMidiSynth(int i, std::shared_ptr<MidiSynth> synth);

		public:
			virtual std::weak_ptr<MidiSynth> getMidiSynth(int i);
			virtual void close();

			SynthRack(std::weak_ptr<SynthRackControls> controls, std::weak_ptr<ctoot::midi::core::MidiSystem> midiSystem, std::weak_ptr<ctoot::audio::system::AudioSystem> audioSystem);

		private:
			friend class SynthRackObserver;
		};

	}
}
