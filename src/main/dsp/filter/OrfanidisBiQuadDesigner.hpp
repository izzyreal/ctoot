#pragma once

#include <vector>

namespace ctoot {
	namespace dsp {
		namespace filter {

			class OrfanidisBiQuadDesigner
			{

			private:
				static float THREE_DB_;
				static constexpr double PI2{ 9.869604401089358 };

			public:
				static std::vector<double> designPeak(float fs, float f0, float fb, float G);
				static std::vector<double> designResonator(float fs, float f0, float fb);
				static std::vector<double> designNotch(float fs, float f0, float fb);
				static std::vector<double> design(float fs, float f0, float fb, float G0, float G, float Gb);

				OrfanidisBiQuadDesigner();

            };

		}
	}
}
