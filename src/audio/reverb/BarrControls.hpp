#pragma once
#include <audio/core/AudioControls.hpp>
#include <audio/reverb/BarrProcess.hpp>

#include <control/ControlLaw.hpp>
#include <control/LinearLaw.hpp>
#include <control/LogLaw.hpp>

#include <control/FloatControl.hpp>

#include <string>
#include <map>
#include <vector>
#include <memory>

namespace ctoot {
	namespace audio {
		namespace reverb {

			class BarrControls
				: public ctoot::audio::core::AudioControls
				, public ctoot::audio::reverb::BarrVariables
			
			{
			public:
				BarrControls();

			private:
				const static int MAX_PRE_DELAY_MS = 200;
				static std::weak_ptr<ctoot::control::ControlLaw> PRE_DELAY_LAW();
				static std::weak_ptr<ctoot::control::ControlLaw> DIFFUSION_LAW();
				static std::weak_ptr<ctoot::control::ControlLaw> SIZE_LAW();

				const static int PRE_DELAY = 0;
				const static int BANDWIDTH = 1;
				const static int INPUT_DIFFUSION = 2;
				const static int DAMPING = 4;
				const static int DECAY = 5;
				const static int DECAY_DIFFUSION = 6;
				const static int SIZE = 7;

				std::weak_ptr<ctoot::control::FloatControl> preDelayControl;
				std::weak_ptr<ctoot::control::FloatControl> bandwidthControl;
				std::weak_ptr<ctoot::control::FloatControl> inputDiffusionControl;
				std::weak_ptr<ctoot::control::FloatControl> dampingControl;
				std::weak_ptr<ctoot::control::FloatControl> decayControl;
				std::weak_ptr<ctoot::control::FloatControl> decayDiffusionControl;
				std::weak_ptr<ctoot::control::FloatControl> sizeControl;

				int preDelaySamples;
				float bandwidth;
				float inputDiffusion;
				float damping, decay;
				float decayDiffusion;
				float size;

			protected:
				void derive(ctoot::control::Control* c) override;

			protected:
				void createControls();
				std::shared_ptr<ctoot::control::FloatControl> createPreDelayControl();
				std::shared_ptr<ctoot::control::FloatControl> createBandwidthControl();
				std::shared_ptr<ctoot::control::FloatControl> createInputDiffusionControl();
				std::shared_ptr<ctoot::control::FloatControl> createDampingControl();
				std::shared_ptr<ctoot::control::FloatControl> createDecayControl();
				std::shared_ptr<ctoot::control::FloatControl> createDecayDiffusionControl();
				std::shared_ptr<ctoot::control::FloatControl> createSizeControl();
				void deriveControls();
				int derivePreDelaySamples();
				float deriveBandwidth();
				float deriveInputDiffusion();
				float deriveDamping();
				float deriveDecay();
				float deriveDecayDiffusion();
				float deriveSize();

			public:
				int getMaxPreDelaySamples();
				int getPreDelaySamples();
				float getBandwidth();
				float getInputDiffusion();
				float getDamping();
				float getDecay();
				float getDecayDiffusion();
				float getSize();
				bool canBypass() { return false; }

				// KB keeps block diffuser length much longer than input diffuser lengths
				// KB keeps delay length a bit less than sum of dif1 and dif2 lengths
				// converted to 44100 from 29761Hz sample rate for original Griesinger literals
			private:
				std::vector<std::vector<int>> sizes = { { 996, 2667, 6598 },
				{ 1777, 3579, 4687 },
				{ 1345, 3936, 6249 },
				{ 1173, 4167, 5512 },
				{ 210, 159, 562, 410 } }; // input diffusers

				std::vector<std::vector<int>> leftTaps = { { 253, 5211 },
				{ 1745, 4111 },
				{ 634, 5873 },
				{ 1423, 5173 } };

				std::vector<std::vector<int>> rightTaps = { { 1111, 3576 },
				{ 568, 4666 },
				{ 1964, 4236 },
				{ 47, 3533 } };

			public:
				std::vector<std::vector<int>> getSizes();
				std::vector<std::vector<int>> getLeftTaps();
				std::vector<std::vector<int>> getRightTaps();

			};
			REGISTER_TYPE(ctoot::audio::reverb::, BarrControls)
		}
	}
}
