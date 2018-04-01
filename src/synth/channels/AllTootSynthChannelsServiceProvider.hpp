#pragma once

#include <synth/spi/TootSynthChannelServiceProvider.hpp>

namespace ctoot {
	namespace synth {

		class SynthChannel;
		class SynthChannelControls;

		namespace channels {
			class AllTootSynthChannelsServiceProvider
				: public ctoot::synth::spi::TootSynthChannelServiceProvider
			{

			public:
				std::shared_ptr<ctoot::synth::SynthChannel> createSynthChannel(std::weak_ptr<ctoot::synth::SynthChannelControls> c) override;

				AllTootSynthChannelsServiceProvider();

			};

		}
	}
}
