#pragma once

#include <audio/delay/DelayTap.hpp>


namespace ctoot {
	namespace audio {
		namespace delay {

			class CabMicingControlsTap
				: public virtual DelayTap
			{

			public:
				float millis{ 1.0f };
				float level{ 0.0f };

			public:
				float getDelayMilliseconds() override;
				float getLevel() override;

			public:
				CabMicingControlsTap();

			};

		}
	}
}
