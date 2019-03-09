#pragma once

namespace ctoot {
	namespace synth {
		namespace modules {
			namespace oscillator {

				class LFOConfig
				{

				public:
					float rateMin{ 0.01f };
					float rateMax{ 1.0f };
					float rate{ 0.1f };
					float deviationMax{ 0.0f };
					float deviation{ 0.0f };

				};

			}
		}
	}
}
