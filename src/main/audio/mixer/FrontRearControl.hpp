#pragma once
#include <control/FloatControl.hpp>

#include <vector>
#include <string>

#define _USE_MATH_DEFINES
#include <cmath>
#define _USE_MATH_DEFINES
#include <math.h>

namespace ctoot {
	namespace audio {
		namespace mixer {

			class FrontRearControl
				: public ctoot::control::FloatControl
			{

			private:
				float front{};
				float rear{};
				static std::vector<std::string> presetNames_;

			public:
				virtual float getFront();
				virtual float getRear();

			public:
				void setValue(float value) override;
				std::vector<std::string> getPresetNames() override;
				void applyPreset(std::string presetName) override;

			public:
				FrontRearControl();

			};

		}
	}
}
