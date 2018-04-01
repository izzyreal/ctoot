#pragma once

#include <cstdint>

namespace ctoot {
	namespace synth {
		namespace modules {
			namespace oscillator {

				class LFOVariables;

				class LFO
				{

				private:
					int32_t shape{ 0 };
					float modulatorPhase{ 0.0f };
					float xDelta{  };
					LFOVariables* vars{  };
					float rateDelta{  };
					double phaseDelta{  };

				public:
					virtual void setSampleRate(int32_t sampleRate);
					virtual void update();
					virtual float getSample();

					LFO(LFOVariables* vars, float initPhase);
					LFO(LFOVariables* vars);

				};

			}
		}
	}
}
