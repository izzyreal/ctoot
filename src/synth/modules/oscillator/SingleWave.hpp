#include <synth/modules/oscillator/Wave.hpp>

#pragma once
namespace ctoot {
	namespace synth {
		namespace modules {
			namespace oscillator {

				class SingleWave
					: public virtual Wave
				{

				private:
					::floatArray* data{  };
					float period{  };

				public:
					::floatArray* getData() override;
					float getPeriod() override;
					float get(float index) override;

					SingleWave(::floatArray* data, float period);

				};

			}
		}
	}
}
