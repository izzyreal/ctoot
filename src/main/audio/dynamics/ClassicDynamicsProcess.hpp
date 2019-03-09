#pragma once

#include <audio/core/SimpleAudioProcess.hpp>

namespace ctoot {
	namespace audio {
		namespace dynamics {

			class DynamicsVariables;

			class ClassicDynamicsProcess
				: public ctoot::audio::core::SimpleAudioProcess
			{

			protected:
				float envelope{  };

			private:
				void init();

			private:
				float gain{  };

			protected:
				bool isPeak{  };
				float threshold{  };
				float inverseThreshold{  };
				float attack{  }, release{  };
				float makeupGain{  }, dryGain{  };
				DynamicsVariables* vars{  };

			private:
				bool wasBypassed{  };
				int32_t sampleRate{  };
				std::vector<std::vector<float>*> samples{  };

			public:
				virtual void clear();

			protected:
				virtual void cacheProcessVariables();

			public:
				int32_t processAudio(ctoot::audio::core::AudioBuffer* buffer) override;

			public:
				virtual float function(float value) = 0;
				virtual float dynamics(float target);

			public:
				ClassicDynamicsProcess(DynamicsVariables* vars);

			public:
				ClassicDynamicsProcess();
			};

		}
	}
}
