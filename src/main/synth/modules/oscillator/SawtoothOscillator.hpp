#pragma once

#include <memory>

namespace ctoot {
	namespace synth {

		class SynthChannel;

		namespace modules {
			namespace oscillator {

				class MultiWave;
				class Wave;

				class SawtoothOscillator
				{

				private:
					static std::weak_ptr<MultiWave> multiWave;
					ctoot::synth::SynthChannel* channel{  };
					std::weak_ptr<Wave> wave{  };
					int32_t waveSize{  };
					int32_t waveIndex{  };
					float k{  };
					float k2{  };
					float increment{ 1.0f };
					float currentIncrement{  };
					float index{ 0.0f };
					float frequency{  };

				public:
					virtual void setSampleRate(int32_t sampleRate);
					virtual void update();
					virtual float getSample(float mod);

					SawtoothOscillator(ctoot::synth::SynthChannel* channel, float frequency);

				};

			}
		}
	}
}
