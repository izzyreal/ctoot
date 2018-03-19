#pragma once

#include <vector>

namespace ctoot {
	namespace dsp {
		namespace filter {

			enum FilterShape;

			class BiQuadDesigner
			{

			private:
				static bool decramped_;
				static double M_LN2_;

			public:
				static std::vector<double> design(FilterShape type, float dbGain, float freq, float srate, float resonance);

			public:
				static bool& decramped();

			};

		}
	}
}
