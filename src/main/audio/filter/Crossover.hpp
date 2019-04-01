#pragma once
#include <stdint.h>
#include <vector>

namespace ctoot {
	namespace audio {
		namespace filter {

			class Crossover
			{
			public:
				virtual void filter(std::vector<float>* source, std::vector<float>* lo, std::vector<float>* hi, int32_t nsamples, int32_t chan) = 0;
				virtual void clear() = 0;
				virtual void setSampleRate(int32_t sampleRate) = 0;
			};

		}
	}
}
