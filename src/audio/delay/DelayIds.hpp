#pragma once

namespace ctoot {
	namespace audio {
		namespace delay {

			class DelayIds	
			{
			public:
				static constexpr int STEREO_MODULATED_DELAY_ID{ int(17) };
				static constexpr int MULTI_TAP_DELAY_ID{ int(18) };
				static constexpr int ROOM_SIMULATOR{ int(19) };
				static constexpr int MODULATED_DELAY_ID{ int(20) };
				static constexpr int TEMPO_DELAY_ID{ int(21) };
				static constexpr int PHASER_ID{ int(22) };
				static constexpr int CAB_MICING_ID{ int(23) };
				static constexpr int WOW_FLUTTER_ID{ int(24) };

			};

		}
	}
}
