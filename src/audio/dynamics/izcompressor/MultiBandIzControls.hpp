#pragma once

#include <audio/dynamics/MultiBandControls.hpp>

namespace ctoot {

	namespace control {
		class FloatControl;
		class ControlLaw;
	}

	namespace audio {
		namespace dynamics {
			namespace izcompressor {

				class MultiBandIzControls
					: public MultiBandControls
				{
				private:
					static std::weak_ptr<ctoot::control::ControlLaw> INPUT_GAIN_LAW();
					std::weak_ptr<ctoot::control::FloatControl> inputGainControl;
					float inputGain{ 1.0f };

				private:
					std::shared_ptr<ctoot::control::FloatControl> createInputGainControl();
					void deriveInputGain();

				public:
					float getInputGain();

				public:
					MultiBandIzControls();

				};
				REGISTER_TYPE(ctoot::audio::dynamics::izcompressor::, MultiBandIzControls);
			}
		}
	}
}
