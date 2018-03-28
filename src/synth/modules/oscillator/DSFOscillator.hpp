#pragma once

namespace ctoot {
	namespace synth {
		namespace modules {
			namespace oscillator {

				class DSFOscillator
				{
				public:
					virtual void update(float a) = 0;
					virtual float getSample() = 0;

				};

			}
		}
	}
}
