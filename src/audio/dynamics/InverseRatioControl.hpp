#pragma once

#include <control/FloatControl.hpp>

#include <string>
#include <vector>

namespace ctoot {
	namespace audio {
		namespace dynamics {

			class DynamicsControls;

			class InverseRatioControl
				: public ctoot::control::FloatControl
			{

			public:
				std::string getValueString() override;
				void applyPreset(std::string name) override;
				std::vector<std::string> getPresetNames() override;

			public:
				InverseRatioControl(DynamicsControls* dynamicsControls);

			public:
				DynamicsControls* dynamicsControls;

			};
		}
	}
}
