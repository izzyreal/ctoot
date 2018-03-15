#pragma once

namespace ctoot {
	namespace audio {
		namespace delay {

			class DelayTap
				
			{
			public:
				virtual float getDelayMilliseconds() = 0;
				virtual float getLevel() = 0;
				
			};

		}
	}
}
