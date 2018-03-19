#pragma once

namespace ctoot {
	namespace audio {
		namespace filter {

			class FilterTools
			{

			private:
				static float LN2_;

			public:
				static float getDampingFactor(float resonance);
				static float getHzBandwidth(float frequency, float resonance);
				static float getOctaveBandwidth(float resonance);

			private:
				static float& LN2();
			};
		}
	}
}
