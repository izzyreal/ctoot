#pragma once

#include <audio/delay/DelayVariables.hpp>


namespace ctoot {
	namespace audio {
		namespace delay {

			class ModulatedDelayProcessVariables
				: public virtual DelayVariables
			{
			public:
				virtual float getDelayMilliseconds() = 0;
				virtual float getRate() = 0;
				virtual float getDepth() = 0;
				virtual float getFeedback() = 0;
				virtual float getWet() = 0;
				virtual float getDry() = 0;
				virtual int getLFOShape() = 0;
				virtual bool isPhaseQuadrature() = 0;
			};

		}
	}
}
