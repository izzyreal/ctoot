#pragma once

#include <synth/spi/SynthChannelServiceProvider.hpp>

namespace ctoot {
	namespace synth {
		namespace spi {

			class TootSynthChannelServiceProvider
				: public SynthChannelServiceProvider
			{

			public:
				TootSynthChannelServiceProvider(std::string description, std::string version);
			};

		}
	}
}
