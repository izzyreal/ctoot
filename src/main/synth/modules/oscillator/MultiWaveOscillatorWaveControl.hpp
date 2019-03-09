#pragma once
#include <control/EnumControl.hpp>

#include <any>

namespace ctoot {
	namespace synth {
		namespace modules {
			namespace oscillator {

				class MultiWaveOscillatorWaveControl
					: public ctoot::control::EnumControl
				{

				public:
					std::vector<std::any> getValues() override;

				public:
					MultiWaveOscillatorWaveControl(int id, std::string name, std::any value);

				};
			}
		}
	}
}
