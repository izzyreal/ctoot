#pragma once

#include <audio/dynamics/MultiBandControls.hpp>

namespace ctoot {
	namespace audio {
		namespace dynamics {

			class MidSideQuadBandControls
				: public MultiBandControls
			{

			public:
				MidSideQuadBandControls();

			};
			REGISTER_TYPE(ctoot::audio::dynamics::, MidSideQuadBandControls);
		}
	}
}
