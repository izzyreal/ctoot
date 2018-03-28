#pragma once

#include <cstdint>

namespace ctoot {
	namespace synth {
		namespace modules {
			namespace mixer {

				class MixerVariables
				{
				public:
					virtual int32_t getCount() = 0;
					virtual float getLevel(int32_t n) = 0;

				};

			}
		}
	}
}
