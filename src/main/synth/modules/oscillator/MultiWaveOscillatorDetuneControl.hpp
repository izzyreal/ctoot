#pragma once

#include <control/FloatControl.hpp>

#include <string>
#include <vector>

namespace ctoot {
	namespace synth {
		namespace modules {
			namespace oscillator {

				class MultiWaveOscillatorDetuneControl
					: public ctoot::control::FloatControl
				{

				private:
					std::vector<std::string> presetNames{ "Off" };

				public:
					std::vector<std::string> getPresetNames() override;
					void applyPreset(std::string presetName) override;

				public:
					MultiWaveOscillatorDetuneControl(int id, std::string name, std::weak_ptr<ctoot::control::ControlLaw> law, float precision, float initialValue);

				};
			}
		}
	}
}
