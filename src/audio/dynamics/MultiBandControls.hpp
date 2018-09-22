#pragma once

#include <audio/core/AudioControls.hpp>

#include <control/IntegerControl.hpp>

namespace ctoot {
	namespace audio {
		namespace dynamics {

			class MultiBandControls
				: public ctoot::audio::core::AudioControls
			{

			private:
				std::weak_ptr<ctoot::control::IntegerControl> linkControl;

			private:
				std::shared_ptr<ctoot::control::IntegerControl> createLinkControl();

			public:
				bool hasOrderedFrequencies() override;
			
				MultiBandControls(std::string name);

			};
		}
	}
}
