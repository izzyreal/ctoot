#pragma once

namespace ctoot {
	namespace synth {
		namespace modules {
			namespace oscillator {

				class OscillatorVariables
				{
				public:
					virtual bool isMaster() = 0;
					virtual float getDetuneFactor() = 0;
					virtual float getSyncThreshold() = 0;

				};

			}
		}
	}
}
