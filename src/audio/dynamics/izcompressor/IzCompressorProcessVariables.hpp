#pragma once

#include <vector>
#include <string>

namespace ctoot {
	namespace audio {
		namespace dynamics {
			namespace izcompressor {

				class IzCompressorProcessVariables
				{
				public:
					virtual void update(float sampleRate) = 0;
					virtual bool isBypassed() = 0;
					virtual float getThreshold() = 0;
					virtual float getInverseThreshold() = 0;
					virtual float getInverseRatio() = 0;
					virtual float getKnee() = 0;
					virtual float getAttack() = 0;
					virtual float getRelease() = 0;
					virtual float getDepth() = 0;
					virtual float getGain() = 0;
					virtual void setDynamicGain(float gain) = 0;
					virtual std::string getDetectionChannelMode() = 0;
					virtual std::string getAttenuationChannelMode() = 0;
					virtual float getInputGain() = 0;

				};

			}
		}
	}
}
