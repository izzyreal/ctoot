#pragma once

#include <cstdint>

namespace ctoot {
	namespace synth {
		namespace modules {
			namespace envelope {

				class EnvelopeVariables
				{

				public:
					virtual void setSampleRate(int32_t rate) = 0;
					virtual int32_t getDelayCount() = 0;
					virtual float getAttackCoeff() = 0;
					virtual int32_t getHoldCount() = 0;
					virtual float getDecayCoeff() = 0;
					virtual float getSustainLevel() = 0;
					virtual float getReleaseCoeff() = 0;

				};

			}
		}
	}
}
