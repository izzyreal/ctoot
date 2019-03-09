#pragma once

#include <vector>

namespace ctoot {
	namespace audio {
		namespace dynamics {

			class MidSideDynamicsProcessVariables
			{
			public:
				virtual void update(float sampleRate) = 0;
				virtual bool isBypassed() = 0;
				virtual std::vector<float> getThreshold() = 0;
				virtual std::vector<float> getInverseThreshold() = 0;
				virtual std::vector<float> getInverseRatio() = 0;
				virtual std::vector<float> getKnee() = 0;
				virtual std::vector<float> getAttack() = 0;
				virtual std::vector<int32_t> getHold() = 0;
				virtual std::vector<float> getRelease() = 0;
				virtual std::vector<float> getDepth() = 0;
				virtual std::vector<float> getGain() = 0;
				virtual void setDynamicGain(float gainM, float gainS) = 0;
			};

		}
	}
}
