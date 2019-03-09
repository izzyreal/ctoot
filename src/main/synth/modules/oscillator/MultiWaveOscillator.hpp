#pragma once

#include <cstdint>
#include <memory>

namespace ctoot {
	namespace synth {

		class SynthChannel;

		namespace modules {
			namespace oscillator {

				class MultiWaveOscillatorVariables;
				class MultiWave;
				class Wave;
				class OscillatorControl;

				class MultiWaveOscillator
				{

				private:
					ctoot::synth::SynthChannel* channel{  };
					MultiWaveOscillatorVariables* vars{  };
					bool master{  };
					std::weak_ptr<MultiWave> multiWave{  };
					std::weak_ptr<Wave> wave{  };
					int32_t waveSize{  };
					int32_t waveIndex{  };
					float k{  };
					float k2{  };
					float increment{ 1.0f };
					float currentIncrement{  };
					bool sync{  };
					float index{ 0.0f };
					float scalar{ 1.0f };
					float offset{ 0.0f };
					float frequency{  };
					float width{  };

				public:
					virtual void setSampleRate(int32_t sampleRate);
					virtual void update();
					virtual float getSample(float mod, float wmod, OscillatorControl* control);

					MultiWaveOscillator(ctoot::synth::SynthChannel* channel, MultiWaveOscillatorVariables* oscillatorVariables, float frequency);

				};

			}
		}
	}
}
