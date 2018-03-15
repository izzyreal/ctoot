#pragma once

#include <audio/spi/TootAudioServiceProvider.hpp>


namespace ctoot {
	namespace audio {
		namespace delay {

			class DelayServiceProvider
				: public ctoot::audio::spi::TootAudioServiceProvider
			{

			public:
				std::shared_ptr<ctoot::audio::core::AudioProcess> createProcessor(std::weak_ptr<ctoot::audio::core::AudioControls> c) override;
				std::shared_ptr<ctoot::audio::core::AudioControls> createControls(int moduleId) override;

			public:
				DelayServiceProvider();

			};
		}
	}
}
