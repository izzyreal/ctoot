#pragma once
#include <cstdint>
#include <vector>

namespace ctoot {
	namespace audio {
		namespace filter {

			class Filter
			{
			public:
				virtual void open() = 0;
				virtual void close() = 0;
				virtual void filter(std::vector<float>* source, std::vector<float>* dest, int32_t length, int32_t chan, bool mix) = 0;
				virtual void clear() = 0;
				virtual void setSampleRate(int32_t sampleRate) = 0;
				//virtual void init() = 0;

			};
		}
	}
}
