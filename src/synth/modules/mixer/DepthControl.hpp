#pragma once

#include <control/FloatControl.hpp>

namespace ctoot {
	namespace synth {
		namespace modules {
			namespace mixer {
				class DepthControl
					: public ctoot::control::FloatControl
				{

				private:
					std::vector<std::string> presetNames{ "Off" };

				public:
					std::vector<std::string> getPresetNames() override;
					void applyPreset(std::string presetName) override;

				};

			}
		}
	}
}
