#pragma once

#include <control/FloatControl.hpp>

namespace ctoot {

	namespace control {
		class ControlLaw;
	}

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

				public:
					DepthControl(int id, std::string name, std::weak_ptr<ctoot::control::ControlLaw> law, float precision, float initialValue);

				};

			}
		}
	}
}
