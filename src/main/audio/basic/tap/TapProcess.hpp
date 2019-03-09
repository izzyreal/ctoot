#pragma once

#include <audio/core/AudioProcess.hpp>

namespace ctoot {
	namespace audio {
		namespace basic {
			namespace tap {

				class TapControls;

				class TapProcess
					: public virtual ctoot::audio::core::AudioProcess
				{

				private:
					TapControls * controls{  };
					ctoot::audio::core::AudioBuffer* tap{  };

				public:
					void open() override;
					int32_t processAudio(::ctoot::audio::core::AudioBuffer* buffer) override;
					void close() override;

					TapProcess(TapControls* controls);
				};
			}
		}
	}
}
