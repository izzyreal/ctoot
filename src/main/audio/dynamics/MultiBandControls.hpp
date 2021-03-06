#pragma once

#include <audio/core/AudioControls.hpp>

#include <control/IntegerControl.hpp>

namespace ctoot {
	namespace audio {
		namespace dynamics {

			class MultiBandControls
				: public ctoot::audio::core::AudioControls
			{

			public:
				bool hasOrderedFrequencies() override;
			
				MultiBandControls(std::string name);

			};
		}
	}
}
