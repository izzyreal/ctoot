#pragma once

namespace ctoot {
	namespace dsp {

		class VolumeUtils
		{

		private:
			static double FACTOR1;
			static constexpr double FACTOR2{ 0.05 };

		public:
			static double lin2log(double dLinear);
			static double log2lin(double dLogarithmic);

		};

	}
}
