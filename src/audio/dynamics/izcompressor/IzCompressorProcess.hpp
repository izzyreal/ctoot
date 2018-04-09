#pragma once

#include <audio/core/SimpleAudioProcess.hpp>

#include <string>
#include <vector>

namespace ctoot {
	namespace audio {
		namespace dynamics {
			namespace izcompressor {

				class IzCompressorProcessVariables;

				class IzCompressorProcess
					: public ctoot::audio::core::SimpleAudioProcess
				{

				protected:
					float envelope = 0.0f;
					bool isPeak{ false };
					float threshold;
					float attack;
					float release;
					float makeupGain;
					std::string detectionChannelMode;
					std::string attenuationChannelMode;
					float inputGain = 1.0f;
					IzCompressorProcessVariables* vars{  };

				private:
					bool wasBypassed{  };
					int32_t sampleRate{ 0 };
					const int32_t NSQUARESUMS{ 10 };
					std::vector<float> squaresums = std::vector<float>(NSQUARESUMS);
					int32_t nsqsum{ 0 };

					std::vector<float>* detectionSamples0;
					std::vector<float>* detectionSamples1;
					std::vector<float>* detectionSamplesM;
					std::vector<float>* detectionSamplesS;

					std::vector<float>* attenuationSamples0;
					std::vector<float>* attenuationSamples1;
					std::vector<float>* attenuationSamplesM;
					std::vector<float>* attenuationSamplesS;

				public:
					virtual void clear();

				protected:
					virtual void cacheProcessVariables();

				public:
					int32_t processAudio(ctoot::audio::core::AudioBuffer* buffer) override;

				protected:
					virtual float function(float value) = 0;
					virtual float dynamics(float target);

				private:
					void calcGain(std::vector<float>* detectionSamples, float& targetGain, const int sampleIndex, const int mslen, const int len, const float sumdiv, float& gain);

				public:
					IzCompressorProcess(IzCompressorProcessVariables* vars);
					IzCompressorProcess(IzCompressorProcessVariables* vars, bool peak);
				};

			}
		}
	}
}
