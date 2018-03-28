#pragma once

namespace ctoot {
	namespace synth {
		namespace modules {
			namespace oscillator {

				class MultiWave;
				class Wave;

				class SawtoothOscillator
				{

				private:
					static MultiWave* multiWave_;
					ctoot::synth::SynthChannel* channel{  };
					Wave* wave{  };
					int32_t waveSize{  };
					int32_t waveIndex{  };
					float k{  };
					float k2{  };
					float increment{  };
					float currentIncrement{  };
					float index{  };
					float frequency{  };
				protected:
					void ctor(ctoot::synth::SynthChannel* channel, float frequency);

				public:
					virtual void setSampleRate(int32_t sampleRate);
					virtual void update();
					virtual float getSample(float mod);

					SawtoothOscillator(ctoot::synth::SynthChannel* channel, float frequency);

				private:
					static MultiWave*& multiWave();
				};

			}
		}
	}
}
