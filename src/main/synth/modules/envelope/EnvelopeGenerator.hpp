#pragma once

#include "EnvelopeGeneratorState.hpp"

#include <cstdint>

namespace ctoot {
	namespace synth {
		namespace modules {
			namespace envelope {

				class EnvelopeVariables;

				class EnvelopeGenerator
				{

				private:
					EnvelopeVariables * vars{  };
					EnvelopeGeneratorState state = COMPLETE;
					int32_t delayCount{  };
					float attackCoeff{  };
					int32_t holdCount{  };
					float decayCoeff{  };
					float sustainLevel{  };
					float releaseCoeff{  };
					float envelope{ 0.0f };

				public:

                    virtual void trigger();

                };

			}
		}
	}
}
