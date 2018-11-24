#pragma once

namespace ctoot {
	namespace audio {
		namespace dynamics {

			class DynamicsControlIds
			{

			public:
				static constexpr int KEY{ 0 };
				static constexpr int THRESHOLD{ 1 };
				static constexpr int RATIO{ 2 };
				static constexpr int KNEE{ 3 };
				static constexpr int ATTACK{ 4 };
				static constexpr int HOLD{ 5 };
				static constexpr int RELEASE{ 6 };
				static constexpr int GAIN{ 7 };
				static constexpr int DRY_GAIN{ 8 };
				static constexpr int DEPTH{ 9 };
				static constexpr int CROSSOVER_FREQUENCY{ 10 };
				static constexpr int HYSTERESIS{ 11 };
				static constexpr int RMS{ 12 };
				static constexpr int DETECTION_CHANNEL_MODE{ 13 };
				static constexpr int ATTENUATION_CHANNEL_MODE{ 14 };
				static constexpr int INPUT_GAIN{ 15 };
				static constexpr int OUTPUT_GAIN{ 16 };
				static constexpr int LOOK_AHEAD{ 17 };
				static constexpr int MUTE{ 18 };
				static constexpr int WET_GAIN{ 19 };
				static constexpr int MASTER_INPUT_GAIN{ 20 };
				static constexpr int MASTER_OUTPUT_GAIN{ 21 };
				static constexpr int SOLO{ 22 };
				static constexpr int BYPASS{ 23 };
				
				
				static constexpr int LINK{ 126 - 10 - 0 };

			};

            
		}
	}
}
