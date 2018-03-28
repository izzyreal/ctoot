#pragma once
namespace ctoot {
	namespace synth {
		namespace modules {
			namespace oscillator {

				class ParabolaMultiWave
					: public MultiWave
				{

				public:
					float getWidthStartFactor(float width) override;
					float getWidthScalar(float width) override;

				protected:
					int32_t partial(::floatArray* data, int32_t length, int32_t partial, int32_t sign, float comp) override;
					void normalise(::floatArray* data, float max) override;

					// Generated

				public:
					ParabolaMultiWave(int32_t size, float fNyquist);

				};

			}
		}
	}
}
