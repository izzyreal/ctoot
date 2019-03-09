#pragma once

#include <audio/spi/TootAudioServiceProvider.hpp>

#include <memory>

namespace ctoot {
	namespace audio {

		namespace core {
			class AudioProcess;
			class AudioControls;
		}

		namespace basic {

			class BasicServiceProvider
				: public ctoot::audio::spi::TootAudioServiceProvider
			{

			public:
				std::shared_ptr<ctoot::audio::core::AudioProcess> createProcessor(std::weak_ptr<ctoot::audio::core::AudioControls> c) override;

				BasicServiceProvider();
			};

		}
	}
}
