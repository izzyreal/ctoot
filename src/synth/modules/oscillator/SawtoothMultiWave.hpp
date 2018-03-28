#pragma once

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
					int32_t partial(::floatArray* data, int32_t length, int32_t partial, int32_t sign, float comp) override;

					// Generated

				public:
					SawtoothMultiWave(int32_t size, float fNyquist);

				};

			}
		}
	}
}
