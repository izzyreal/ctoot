#pragma once

namespace ctoot {
	namespace synth {
		namespace modules {
			namespace amplifier {

				class AmplifierVariables
				{
				public:
					virtual float getVelocityTrack() = 0;
					virtual float getLevel() = 0;

				};
			}
		}
	}
}
