#pragma once

#include <cstdint>

namespace ctoot {

	namespace audio {
		namespace core {
			class AudioBuffer;
		}
	}

	namespace synth {

		class PolyphonicSynthChannelVoice
		{
		public:
			virtual int32_t getPitch() = 0;
			virtual void release() = 0;
			virtual bool isReleased() = 0;
			virtual void stop() = 0;
			virtual void setSampleRate(int32_t sr) = 0;
			virtual bool mix(ctoot::audio::core::AudioBuffer* buffer) = 0;

		};

	}
}
