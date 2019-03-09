#pragma once

#include <audio/core/SimpleAudioProcess.hpp>

#include <vector>

namespace ctoot {
	namespace audio {
		namespace dynamics {

			class MidSideDynamicsProcessVariables;

			class MidSideDynamicsProcess
				: public ctoot::audio::core::SimpleAudioProcess
			{

			protected:
				std::vector<float> envelope = std::vector<float>(2);
				bool isPeak{ false };
				std::vector<float> threshold{  };
				std::vector<float> attack{  };
				std::vector<float> release{  };
				std::vector<float> makeupGain{  };
				MidSideDynamicsProcessVariables* vars{  };

			private:
				bool wasBypassed{  };
				int32_t sampleRate{ 0 };
				const int32_t NSQUARESUMS{ 10 };
				std::vector<float> squaresumsM = std::vector<float>(NSQUARESUMS);
				std::vector<float> squaresumsS = std::vector<float>(NSQUARESUMS);
				int32_t nsqsum{ 0 };
				std::vector<float>* samplesM{  };
				std::vector<float>* samplesS{  };

			public:
				virtual void clear();

			protected:
				virtual void cacheProcessVariables();

			public:
				int32_t processAudio(ctoot::audio::core::AudioBuffer* buffer) override;

			protected:
				virtual float function(int32_t i, float value) = 0;
				virtual float dynamics(int32_t i, float target);

			public:
				MidSideDynamicsProcess(MidSideDynamicsProcessVariables* vars);
				MidSideDynamicsProcess(MidSideDynamicsProcessVariables* vars, bool peak);
			};

		}
	}
}
