#pragma once

namespace ctoot {
	namespace audio {
		namespace core {

			class KVolumeUtils
			{

			private:
				static constexpr double K{ 20.0 };

			public:
                static double log2lin(double dLogarithmic);
			};
		}
	}
}
