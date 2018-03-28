#pragma once

namespace ctoot {
	namespace synth {
		namespace modules {
			namespace oscillator {

				class LFO
				{

				private:
					int32_t shape{  };
					float modulatorPhase{  };
					float xDelta{  };
					LFOVariables* vars{  };
					float rateDelta{  };
					double phaseDelta{  };
				protected:
					void ctor(LFOVariables* vars, float initPhase);
					void ctor(LFOVariables* vars);

				public:
					virtual void setSampleRate(int32_t sampleRate);
					virtual void update();
					virtual float getSample();

					LFO(LFOVariables* vars, float initPhase);
					LFO(LFOVariables* vars);

				private:
					void init();
				};

			}
		}
	}
}
