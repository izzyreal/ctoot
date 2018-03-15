#pragma once

#include <audio/core/AudioProcess.hpp>


namespace ctoot {
	namespace audio {
		namespace delay {

			class TempoDelayProcessVariables;
			class DelayBuffer;

			class TempoDelayProcess
				: public virtual ctoot::audio::core::AudioProcess
			{

			private:
				DelayBuffer * delayBuffer{  };
				DelayBuffer* tappedBuffer{  };
				//::uk::org::toot::misc::Tempo_Listener* tempoListener{  };
				TempoDelayProcessVariables* vars{  };
				bool wasBypassed{  };
				float bpm{  };
				float meansquare{  };
				float meanK{  };
				float smoothedMix{  };

			public:
				void open() override;
				int processAudio(ctoot::audio::core::AudioBuffer* buffer) override;
				void close() override;

			public:
				virtual int msToSamples(float ms, float sr);

			public:
				TempoDelayProcess(TempoDelayProcessVariables* vars);

			};

		}
	}
}
