#pragma once

#include <audio/spi/TootAudioServiceProvider.hpp>

#include <audio/reverb/BarrProcess.hpp>
#include <audio/core/AudioProcess.hpp>
#include <audio/core/AudioControls.hpp>

#include <memory>

namespace ctoot {
	namespace audio {
		namespace reverb {

			class ReverbServiceProvider
				: public ctoot::audio::spi::TootAudioServiceProvider
			{

			public:
				std::shared_ptr<ctoot::audio::core::AudioProcess> createProcessor(std::weak_ptr<ctoot::audio::core::AudioControls> c) override;

			public:
				ReverbServiceProvider();

			};
		}
	}
}
