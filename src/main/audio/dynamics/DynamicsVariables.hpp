#pragma once

#include <string>

namespace ctoot {
	namespace audio {

		namespace core {
			class AudioBuffer;
		}

		namespace dynamics {

			class DynamicsVariables
			{

			public:
				virtual void update(float sampleRate) = 0;
				virtual bool isBypassed() = 0;
				virtual bool isRMS() = 0;
				virtual float getThreshold() = 0;
				virtual float getInverseThreshold() = 0;
				virtual float getThresholddB() = 0;
				virtual float getInverseRatio() = 0;
				virtual float getKneedB() = 0;
				virtual float getAttack() = 0;
				virtual int32_t getHold() = 0;
				virtual float getRelease() = 0;
				virtual float getDepth() = 0;
				virtual float getDryGain() = 0;
				virtual float getWetGain() = 0;
				virtual float getGain() = 0;
				virtual float getHysteresis() = 0;
				virtual void setDynamicGain(float gain) = 0;
				virtual ctoot::audio::core::AudioBuffer* getKeyBuffer() = 0;
				virtual std::string getDetectionChannelMode() = 0;
				virtual std::string getAttenuationChannelMode() = 0;
				virtual float getInputGain() = 0;
				virtual float getOutputGain() = 0;
				virtual float getLookAhead() = 0;
				virtual bool getMute() = 0;
				virtual bool getSolo() = 0;

			};

		}
	}
}
