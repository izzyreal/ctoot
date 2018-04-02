#pragma once

#include <synth/modules/oscillator/MultiWave.hpp>

namespace ctoot {
	namespace synth {
		namespace modules {
			namespace oscillator {

				class SawtoothMultiWave
					: public MultiWave
				{

				public:
					float getWidthOffset(float width) override;

				protected:
					int32_t partial(std::vector<float>* data, int32_t length, int32_t partial, int32_t sign, float comp) override;

				public:
					SawtoothMultiWave();

				};

			}
		}
	}
}
