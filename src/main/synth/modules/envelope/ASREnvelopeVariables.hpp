#pragma once

#include <cstdint>

namespace ctoot {
	namespace synth {
		namespace modules {
			namespace envelope {

				class ASREnvelopeVariables
				{
				public:
					virtual void setSampleRate(int32_t rate) = 0;
					virtual float getAttackCoeff() = 0;
					virtual bool getSustain() = 0;
					virtual float getReleaseCoeff() = 0;
				};

			}
		}
	}
}
