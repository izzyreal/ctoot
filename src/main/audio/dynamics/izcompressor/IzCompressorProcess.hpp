#pragma once

#include <audio/core/SimpleAudioProcess.hpp>

#include <collections/StereoCircularTBuffer.hpp>

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
					float lookAhead;
					float makeupGain;
					std::string detectionChannelMode;
					std::string attenuationChannelMode;
					float inputGain = 1.0f;
					float outputGain = 1.0f;
					IzCompressorProcessVariables* vars{  };
					bool mute{ false };
					float dryGain = 1.0f;
					float wetGain = 1.0f;

				private:
					std::unique_ptr<moduru::io::StereoCircularTBuffer> lab;
					std::unique_ptr<moduru::io::StereoCircularTBuffer> dryBuffer;
					bool wasBypassed{  };
					int32_t sampleRate{ 0 };
					const int32_t NSQUARESUMS{ 10 };
					const float MAX_LOOK_AHEAD{ 15.0f };
					std::vector<float> squaresums = std::vector<float>(NSQUARESUMS);
					int32_t nsqsum{ 0 };
					float smoothedInputGain{ 1.0f };
					float smoothedDryGain{ 1.0f };
					float smoothedWetGain{ 1.0f };

					//std::vector<float>* attenuationSamples0;
					//std::vector<float>* attenuationSamples1;

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
					void calcGain(std::vector<float>& detectionSamples, float& targetGain, const int sampleIndex, const int mslen, const int len, const float sumdiv, float& gain);

				public:
					IzCompressorProcess(IzCompressorProcessVariables* vars);
					IzCompressorProcess(IzCompressorProcessVariables* vars, bool peak);

					~IzCompressorProcess();
				};

			}
		}
	}
}
