#pragma once

#include <audio/delay/DelayVariables.hpp>

#include <vector>

namespace ctoot {
	namespace audio {
		namespace delay {

			class WowFlutterProcessVariables
				: public virtual DelayVariables
			{
			public:
				virtual float getLevel() = 0;
				virtual std::vector<float> getAmplitudes() = 0;
				virtual int getFrequencyUid() = 0;
				virtual std::vector<float> getFrequencies() = 0;
			};

		}
	}
}
