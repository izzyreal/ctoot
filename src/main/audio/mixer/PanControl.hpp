#pragma once
#include <audio/mixer/LCRControl.hpp>
#define _USE_MATH_DEFINES
#include <cmath>
#define _USE_MATH_DEFINES
#include <math.h>

namespace ctoot {
	namespace audio {
		namespace mixer {

			class PanControl
				  : public LCRControl
			{

			private:
				float left{};
				float right{};

			public:
				float getLeft() override;
				float getRight() override;
				void setValue(float value) override;

			public:
				PanControl();
			};

		}
	}
}
