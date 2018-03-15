#pragma once

#include <audio/core/AudioProcess.hpp>


namespace ctoot {
	namespace audio {
		namespace delay {

			class DelayBuffer;
			class MultiTapDelayProcessVariables;

			class MultiTapDelayProcess
				: public virtual ctoot::audio::core::AudioProcess
			{

			private:
				DelayBuffer* delayBuffer{ nullptr };
				DelayBuffer* tappedBuffer{ nullptr };
				MultiTapDelayProcessVariables* vars{  };
				bool wasBypassed{  };

			public:
				void open() override;
				int processAudio(ctoot::audio::core::AudioBuffer* buffer) override;
				void close() override;
	
			public:
				MultiTapDelayProcess(MultiTapDelayProcessVariables* vars);

			};

		}
	}
}
