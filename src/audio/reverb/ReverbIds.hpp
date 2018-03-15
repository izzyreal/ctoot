#pragma once

#include <audio/id/TootAudioControlsId.hpp>

namespace ctoot {
	namespace audio {
		namespace reverb {

			struct ReverbIds {
				static const int PLATE_ID = ctoot::audio::id::TootAudioControlsId::REVERB_BASE_ID;
				static const int BARR_ID = ctoot::audio::id::TootAudioControlsId::REVERB_BASE_ID + 1;
			};
		}
	}
}
