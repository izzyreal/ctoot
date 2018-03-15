#pragma once

#include <audio/core/AudioProcess.hpp>
#include <audio/core/AudioBuffer.hpp>

#include <audio/delay/CabMicingProcess_Variables.hpp>

namespace ctoot {
	namespace audio {
		namespace delay {

			class DelayBuffer;

			class CabMicingProcess
				: public virtual ctoot::audio::core::AudioProcess
			{

			private:
				DelayBuffer* delayBuffer{ nullptr };
				CabMicingProcess_Variables* vars{  };
				bool wasBypassed{  };

			public:
				void open() override;
				int processAudio(ctoot::audio::core::AudioBuffer* buffer) override;
				void close() override;
				
			public:
				CabMicingProcess(CabMicingProcess_Variables* vars);
			};

		}
	}
}
