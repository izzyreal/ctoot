#pragma once

#include <audio/core/SimpleAudioProcess.hpp>

#include <vector>

namespace ctoot {
	namespace audio {
		namespace dynamics {

			class DynamicsVariables;

			class DynamicsProcess
				: public ctoot::audio::core::SimpleAudioProcess
			{

			private:
				void init();

			protected:
				float envelope{  };
				bool isPeak{  };
				float threshold{  };
				float attack{  }, release{  };
				float makeupGain{  }, dryGain{  };
				DynamicsVariables* vars{  };

			private:
				bool wasBypassed{  };
				int32_t sampleRate{  };
				int32_t NSQUARESUMS{  };
				std::vector<float> squaresums{  };
				int32_t nsqsum{  };
				std::vector<std::vector<float>*> samples{  };
				std::vector<std::vector<float>*> tapSamples{  };
				std::vector<std::vector<float>*> keySamples{  };
			
			public:
				virtual void clear();

			protected:
				virtual void cacheProcessVariables();

			public:
				int32_t processAudio(ctoot::audio::core::AudioBuffer* buffer) override;

			protected:
				virtual float function(float value) = 0;
				virtual float dynamics(float target);

			public:
				DynamicsProcess(DynamicsVariables* vars);
				DynamicsProcess(DynamicsVariables* vars, bool peak);
			};

		}
	}
}
