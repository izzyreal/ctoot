#pragma once

#include <cstdint>

namespace ctoot {
	namespace synth {
		namespace modules {
			namespace filter {

				class FormantFilterVariables
				{

				public:
					virtual int32_t size() = 0;
					virtual float getFrequency(int32_t n) = 0;
					virtual float getLevel(int32_t n) = 0;
					virtual float getFreqencyShift() = 0;
					virtual float getResonance() = 0;
					virtual void setSampleRate(int32_t rate) = 0;
					virtual bool isBypassed() = 0;

				};

			}
		}
	}
}
