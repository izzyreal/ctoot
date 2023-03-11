#pragma once

#include <dsp/filter/FilterShape.hpp>

#include <vector>

namespace ctoot {
	namespace dsp {
		namespace filter {

//            enum FilterShape;

			class BiQuadDesigner
			{

			private:
				static bool decramped_;

			public:
				static std::vector<double> design(FilterShape type, float dbGain, float freq, float srate, float resonance);

            };

		}
	}
}
