#pragma once

namespace ctoot {
	namespace synth {
		namespace modules {
			namespace oscillator {

				class UnisonVariables
				{
				public:
					virtual int32_t getOscillatorCount() = 0;
					virtual float getPitchSpread() = 0;
					virtual float getPhaseSpread() = 0;

				};

			}
		}
	}
}
