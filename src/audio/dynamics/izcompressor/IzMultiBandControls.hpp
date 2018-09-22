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

				class IzMultiBandControls
					: public MultiBandControls
				{
				private:
					static std::weak_ptr<ctoot::control::ControlLaw> INPUT_GAIN_LAW();
					static std::weak_ptr<ctoot::control::ControlLaw> OUTPUT_GAIN_LAW();
					std::weak_ptr<ctoot::control::FloatControl> inputGainControl;
					std::weak_ptr<ctoot::control::FloatControl> outputGainControl;
					float inputGain{ 1.0f };
					float outputGain{ 1.0f };

				private:
					std::shared_ptr<ctoot::control::FloatControl> createInputGainControl();
					void deriveInputGain();
					std::shared_ptr<ctoot::control::FloatControl> createOutputGainControl();
					void deriveOutputGain();

				public:
					float getInputGain();
					float getOutputGain();

				public:
					IzMultiBandControls();

				};
				REGISTER_TYPE(ctoot::audio::dynamics::izcompressor::, IzMultiBandControls);
			}
		}
	}
}
