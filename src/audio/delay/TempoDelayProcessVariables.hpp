#pragma once

#include <audio/delay/DelayVariables.hpp>

namespace ctoot {
	namespace audio {
		namespace delay {

			class TempoDelayProcessVariables
				: public virtual DelayVariables
			{
			public:
				virtual float getDelayFactor() = 0;
				virtual float getFeedback() = 0;
				virtual float getMix() = 0;
				virtual float getDucking() = 0;
				virtual float getLowpassCoefficient() = 0;				
			};

		}
	}
}
