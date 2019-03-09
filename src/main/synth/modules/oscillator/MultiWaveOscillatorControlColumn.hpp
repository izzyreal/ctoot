#pragma once

#include <control/ControlColumn.hpp>

namespace ctoot {
	namespace synth {
		namespace modules {
			namespace oscillator {

				class MultiWaveOscillatorControlColumn
					: public ctoot::control::ControlColumn
				{

				public:
					float getAlignmentY() override {
						return 0.20f;
					}

				};

			}
		}
	}
}
