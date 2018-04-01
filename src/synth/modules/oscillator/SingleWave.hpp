#include <synth/modules/oscillator/Wave.hpp>

#include <vector>

#pragma once
namespace ctoot {
	namespace synth {
		namespace modules {
			namespace oscillator {

				class SingleWave
					: public virtual Wave
				{

				private:
					std::vector<float> data{  };
					float period{  };

				public:
					std::vector<float>* getData() override;
					float getPeriod() override;
					float get(float index) override;

					SingleWave(std::vector<float> data, float period);

				};

			}
		}
	}
}
