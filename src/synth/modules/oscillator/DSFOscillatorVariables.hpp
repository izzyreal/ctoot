#pragma once

namespace ctoot {
	namespace synth {
		namespace modules {
			namespace oscillator {

				class DSFOscillatorVariables
				{
				public:
					virtual int32_t getRatioNumerator() = 0;
					virtual int32_t getRatioDenominator() = 0;
					virtual int32_t getPartialCount() = 0;
					virtual float getPartialRolloffFactor() = 0;
					virtual int32_t getPartialRolloffInt() = 0;
					virtual bool canUseWolfram() = 0;

				};

			}
		}
	}
}
