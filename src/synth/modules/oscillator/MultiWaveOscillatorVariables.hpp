#pragma once

#include <synth/modules/oscillator/OscillatorVariables.hpp>

#include <cstdint>
#include <memory>

namespace ctoot {
	namespace synth {
		namespace modules {
			namespace oscillator {

				class MultiWave;

				class MultiWaveOscillatorVariables
					: public virtual OscillatorVariables
				{
				public:
					virtual std::weak_ptr<MultiWave> getMultiWave() = 0;
					virtual int32_t getOctave() = 0;
					virtual float getWidth() = 0;

				};

			}
		}
	}
}
