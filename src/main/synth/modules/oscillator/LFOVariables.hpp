#pragma once

namespace ctoot {
	namespace synth {
		namespace modules {
			namespace oscillator {

				class LFOVariables
				{
				public:
					virtual float getFrequency() = 0;
					virtual float getDeviation() = 0;
					virtual bool isSine() = 0;

				};
			}
		}
	}
}
