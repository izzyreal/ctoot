#pragma once

#include <audio/dynamics/MultiBandControls.hpp>

namespace ctoot {
	namespace audio {
		namespace dynamics {
			namespace izcompressor {

				class MultiBandIzControls
					: public MultiBandControls
				{

				public:
					MultiBandIzControls();

				};
				REGISTER_TYPE(ctoot::audio::dynamics::izcompressor::, MultiBandIzControls);
			}
		}
	}
}
