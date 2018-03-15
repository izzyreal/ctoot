#pragma once

#include <audio/delay/DelayVariables.hpp>

#include <memory>

namespace ctoot {
	namespace audio {
		namespace delay {

			class DelayTap;

			class MultiTapDelayProcessVariables
				: public virtual DelayVariables
			{
			public:
				virtual std::vector<std::weak_ptr<DelayTap>> getTaps(int chan) = 0;
				virtual float getFeedback() = 0;
				virtual float getMix() = 0;
				virtual int getChannelCount() = 0;
				virtual float getDelayFactor() = 0;
			};

		}
	}
}
