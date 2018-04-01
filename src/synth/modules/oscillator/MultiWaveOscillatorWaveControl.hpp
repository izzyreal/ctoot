#pragma once
#include <control/EnumControl.hpp>

#include <boost/any.hpp>

namespace ctoot {
	namespace synth {
		namespace modules {
			namespace oscillator {

				class MultiWaveOscillatorWaveControl
					: public ctoot::control::EnumControl
				{

				public:
					std::vector<boost::any> getValues() override;

				public:
					MultiWaveOscillatorWaveControl(int id, std::string name, boost::any value);

				};
			}
		}
	}
}
