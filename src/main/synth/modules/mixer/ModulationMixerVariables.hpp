#pragma once

#include <vector>
#include <cstdint>

namespace ctoot {
	namespace synth {
		namespace modules {
			namespace mixer {

				class ModulationMixerVariables
				{
				public:
					virtual int32_t getCount() = 0;
					virtual float getDepth(int32_t n) = 0;
					virtual std::vector<float> getDepths() = 0;

				};

			}
		}
	}
}
