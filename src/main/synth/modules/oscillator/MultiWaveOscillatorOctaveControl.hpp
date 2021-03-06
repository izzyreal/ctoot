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
					std::vector<nonstd::any> getValues() override;

				public:
					MultiWaveOscillatorOctaveControl(int id, std::string name, nonstd::any value);

				};

			}
		}
	}
}
