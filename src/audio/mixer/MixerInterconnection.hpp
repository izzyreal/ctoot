#pragma once
#include <audio/core/AudioProcess.hpp>

#include <memory>

namespace ctoot {
	namespace audio {
		namespace mixer {

			class MixerInterconnection
			{
			public:
				virtual std::weak_ptr<ctoot::audio::core::AudioProcess> getInputProcess() = 0;
				virtual std::weak_ptr<ctoot::audio::core::AudioProcess> getOutputProcess() = 0;

			};

		}
	}
}
