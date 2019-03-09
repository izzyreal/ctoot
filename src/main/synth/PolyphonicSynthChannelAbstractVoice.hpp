#pragma once

#include <synth/PolyphonicSynthChannelVoice.hpp>

namespace ctoot {

	namespace audio {
		namespace core {
			class AudioBuffer;
		}
	}

	namespace synth {

		class PolyphonicSynthChannel;

		class PolyphonicSynthChannelAbstractVoice
			: public virtual PolyphonicSynthChannelVoice
		{

		protected:
			int32_t pitch{  };
			int32_t velocity{  };
			float amplitude{  };
			float frequency{  };
			bool release_{ false };
			bool stop_{ false };

		public:
			int32_t getPitch() override;
			void release() override;
			bool isReleased() override;
			void stop() override;
			bool mix(ctoot::audio::core::AudioBuffer* buffer) override;

		protected:
			virtual float getSample() = 0;
			virtual bool isComplete() = 0;

		public:
			PolyphonicSynthChannelAbstractVoice(int32_t pitch, int32_t velocity);

		};

	}
}
