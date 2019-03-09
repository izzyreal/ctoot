#pragma once
#include <control/FloatControl.hpp>

namespace ctoot {
	namespace synth {
		namespace modules {
			namespace oscillator {

				class MultiWaveOscillatorWidthControl
					: public ctoot::control::FloatControl
				{

				private:
					std::vector<std::string> presetNames{ "50%" };

				public:
					std::vector<std::string> getPresetNames() override;
					void applyPreset(std::string presetName) override;

				public:
					MultiWaveOscillatorWidthControl(int id, std::string name, std::weak_ptr<ctoot::control::ControlLaw> law, float precision, float initialValue);

				};
			}
		}
	}
}
