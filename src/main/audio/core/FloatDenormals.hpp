#include <cmath>
#include <vector>

namespace ctoot {
	namespace audio {
		namespace core {

			class FloatDenormals {

			public:
				static const float THRESHOLD;

			public:
				static const bool isDenormal(float x) {
					return x != 0.f && abs(x) < THRESHOLD;
				}

                static const float zeroDenorm(float x) {
					return abs(x) < THRESHOLD ? 0.f : x;
				}

            };

		}
	}
}
