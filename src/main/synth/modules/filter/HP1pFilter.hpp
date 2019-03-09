#pragma once

#include <synth/modules/filter/LP1pFilter.hpp>

#include <cstdint>

namespace ctoot {
	namespace synth {
		namespace modules {
			namespace filter {
				class HP1pFilter
					: public LP1pFilter
				{

				public:
					float filter(float sample) override;

					HP1pFilter(float freq, int32_t rate);
				};

			}
		}
	}
}
