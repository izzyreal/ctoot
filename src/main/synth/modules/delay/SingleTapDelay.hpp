#pragma once

#include <vector>
#include <stdint.h>

namespace ctoot {
	namespace synth {
		namespace modules {
			namespace delay {

				class SingleTapDelay
				{

				private:
					std::vector<float> delayLine{  };
					int32_t ntaps{  };
					int32_t wrpos{  };
					int32_t rdpos{ 0 };
					int32_t delaySamples{  };

				public:
					virtual float getSample(float in);

					SingleTapDelay(int32_t ntaps);
				};

			}
		}
	}
}
