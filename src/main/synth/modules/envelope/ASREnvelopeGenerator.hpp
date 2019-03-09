#pragma once

#include "ASREnvelopeGeneratorState.hpp"

namespace ctoot {
	namespace synth {
		namespace modules {
			namespace envelope {

				class ASREnvelopeVariables;

				class ASREnvelopeGenerator
				{

				private:
					ASREnvelopeGeneratorState state = ATTACK;
					float attackCoeff{  };
					bool sustain{  };
					float releaseCoeff{  };
					float envelope{ 0.0f };

				public:
					virtual float getEnvelope(bool release);
					virtual bool isComplete();

					ASREnvelopeGenerator(ASREnvelopeVariables* vars);

				};

			}
		}
	}
}
