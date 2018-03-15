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
				
				static const bool isDenormalOrZero(float x) {
					return abs(x) < THRESHOLD;
				}

				static const float zeroDenorm(float x) {
					return abs(x) < THRESHOLD ? 0.f : x;
				}

				static const void zeroDenorms(std::vector<float>* f, int len) {
					for (int i = 0; i < len; i++) {
						(*f)[i] = zeroDenorm((*f)[i]);
					}
				}

				static const int countDenorms(std::vector<float>* f, int len) {
					int count = 0;
					for (int i = 0; i < len; i++) {
						if (isDenormal((*f)[i])) count++;
					}
					return count;
				}

			};

		}
	}
}
