#pragma once

#include <audio/core/AudioControls.hpp>
#include <audio/delay/PhaserProcessVariables.hpp>

#include <control/FloatControl.hpp>
#include <control/ControlLaw.hpp>

#include <memory>

namespace ctoot {
	namespace audio {
		namespace delay {
			
			class StagesControl;

			class PhaserControls
				: public ctoot::audio::core::AudioControls
				, public virtual PhaserProcessVariables
			{

			private:
				static std::weak_ptr<ctoot::control::ControlLaw> RATE_LAW();

			public:
				static constexpr int RATE_ID{ 1 };
				static constexpr int DEPTH_ID{ 2 };
				static constexpr int FEEDBACK_ID{ 3 };
				static constexpr int STAGES_ID{ 0 };

			private:
				std::weak_ptr<ctoot::control::FloatControl> rateControl;
				std::weak_ptr<ctoot::control::FloatControl> depthControl;
				std::weak_ptr<ctoot::control::FloatControl> feedbackControl;
				std::weak_ptr<StagesControl> stagesControl;
				float rate{  }, depth{  }, feedback{  };
				int stages{ 4 };

			public: /* protected */
				void derive(ctoot::control::Control* c) override;
				virtual std::shared_ptr<ctoot::control::FloatControl> createRateControl();
				virtual std::shared_ptr<ctoot::control::FloatControl> createDepthControl();
				virtual std::shared_ptr<ctoot::control::FloatControl> createFeedbackControl();

			public:
				float getDepth() override;
				float getFeedback() override;
				float getRate() override;
				int getStages() override;


			public:
				PhaserControls();

			public:
				virtual bool isBypassed();

			};
			REGISTER_TYPE(ctoot::audio::delay::, PhaserControls)
		}
	}
}
