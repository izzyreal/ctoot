#pragma once

#include <control/EnumControl.hpp>

namespace ctoot {
	namespace synth {
		namespace modules {
			namespace oscillator {

				class MultiWaveOscillatorOctaveControl
					: public ctoot::control::EnumControl
				{

				public:
					std::vector<std::any> getValues() override;

				public:
					MultiWaveOscillatorOctaveControl(int id, std::string name, std::any value);

				};

			}
		}
	}
}
