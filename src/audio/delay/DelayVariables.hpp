#pragma once

namespace ctoot {
	namespace audio {
		namespace delay {

			class DelayVariables
			{
			public:
				virtual float getMaxDelayMilliseconds() = 0;
				virtual bool isBypassed() = 0;
			};

		}
	}
}

