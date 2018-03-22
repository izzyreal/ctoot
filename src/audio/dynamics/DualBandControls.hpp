#pragma once

#include <audio/dynamics/MultiBandControls.hpp>

namespace ctoot {
	namespace audio {
		namespace dynamics {

			class DualBandControls
				: public MultiBandControls
			{

			public:
				DualBandControls();

			};
			//REGISTER_TYPE(ctoot::audio::dynamics::, DualBandControls)
		}
	}
}
