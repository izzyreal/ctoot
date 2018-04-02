#pragma once

#include <synth/spi/SynthServiceProvider.hpp>

namespace ctoot {
	namespace synth {
		namespace synths {
			namespace multi {

				class MultiSynthServiceProvider
					: public ctoot::synth::spi::SynthServiceProvider
				{

				public:
					std::shared_ptr<ctoot::synth::MidiSynth> createSynth(std::weak_ptr<ctoot::synth::SynthControls> c) override;

					MultiSynthServiceProvider();

				};

			}
		}
	}
}
