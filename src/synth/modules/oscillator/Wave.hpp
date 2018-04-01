#pragma once

#include <vector>

namespace ctoot {
	namespace synth {
		namespace modules {
			namespace oscillator {

				class Wave
				{
				public:
					virtual std::vector<float>* getData() = 0;
					virtual float getPeriod() = 0;
					virtual float get(float index) = 0;

				};

			}
		}
	}
}
