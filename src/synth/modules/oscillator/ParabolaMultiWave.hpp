#pragma once

#include <synth/modules/oscillator/MultiWave.hpp>

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
					int32_t partial(std::vector<float>* data, int32_t length, int32_t partial, int32_t sign, float comp) override;
					void normalise(std::vector<float>* data, float max) override;

				public:
					ParabolaMultiWave();

				};

			}
		}
	}
}
