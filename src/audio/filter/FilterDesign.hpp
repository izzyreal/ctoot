#pragma once

#include <cstdint>

namespace ctoot {
	namespace audio {
		namespace filter {

			class FilterSpecification;

			class FilterDesign
			{
			public:
				virtual void design(int32_t sampleRate) = 0;
				virtual FilterSpecification* getFilterSpecification() = 0;
			};

		}
	}
}
