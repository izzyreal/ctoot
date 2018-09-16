#pragma once

namespace ctoot {
	namespace audio {
		namespace dynamics {

			class DynamicsControlIds
			{

			public:
				static constexpr int32_t KEY{ 0 };
				static constexpr int32_t THRESHOLD{ 1 };
				static constexpr int32_t RATIO{ 2 };
				static constexpr int32_t KNEE{ 3 };
				static constexpr int32_t ATTACK{ 4 };
				static constexpr int32_t HOLD{ 5 };
				static constexpr int32_t RELEASE{ 6 };
				static constexpr int32_t GAIN{ 7 };
				static constexpr int32_t DRY_GAIN{ 8 };
				static constexpr int32_t DEPTH{ 9 };
				static constexpr int32_t CROSSOVER_FREQUENCY{ 10 };
				static constexpr int32_t HYSTERESIS{ 11 };
				static constexpr int32_t RMS{ 12 };
				static constexpr int32_t DETECTION_CHANNEL_MODE{ 13 };
				static constexpr int32_t ATTENUATION_CHANNEL_MODE{ 14 };
				static constexpr int32_t INPUT_GAIN{ 15 };
				static constexpr int32_t OUTPUT_GAIN{ 16 };
				static constexpr int32_t LOOK_AHEAD{ 17 };
				static constexpr int32_t MUTE{ 18 };
				static constexpr int32_t WET_GAIN{ 19 };
				static constexpr int32_t MASTER_INPUT_GAIN{ 20 };
				static constexpr int32_t MASTER_OUTPUT_GAIN{ 21 };

			};

		}
	}
}
