#pragma once
#include <control/EnumControl.hpp>

#include <thirdp/any.hpp>

namespace ctoot {
	namespace synth {
		namespace modules {
			namespace oscillator {

				class MultiWaveOscillatorWaveControl
					: public ctoot::control::EnumControl
				{

				public:
					std::vector<nonstd::any> getValues() override;

				public:
					MultiWaveOscillatorWaveControl(int id, std::string name, nonstd::any value);

				};
			}
		}
	}
}
