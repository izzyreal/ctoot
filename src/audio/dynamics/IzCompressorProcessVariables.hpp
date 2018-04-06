#pragma once

#include <vector>

namespace ctoot {
	namespace audio {
		namespace dynamics {

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
			};

		}
	}
}
