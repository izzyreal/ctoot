#pragma once

#include <audio/dynamics/MultiBandControls.hpp>

namespace ctoot {
	namespace audio {
		namespace dynamics {

			class QuadBandControls
				: public MultiBandControls
			{

			public:
				QuadBandControls();

			};
			REGISTER_TYPE(ctoot::audio::dynamics::, QuadBandControls);
		}
	}
}
