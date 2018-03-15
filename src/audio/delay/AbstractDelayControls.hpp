#pragma once

#include <audio/core/AudioControls.hpp>
#include <control/BooleanControl.hpp>
#include <control/FloatControl.hpp>

#include <string>
#include <memory>

namespace ctoot {
	namespace audio {
		namespace delay {
			class AbstractDelayControls
				: public ctoot::audio::core::AudioControls
			{

			public:
				typedef ctoot::audio::core::AudioControls super;

			private:
				static constexpr int FEEDBACK_INVERT_ID{ int(121) };
				static constexpr int FEEDBACK_ID{ int(122) };

			public:
				static constexpr int MIX_ID{ int(124) };
				static constexpr int DELAY_FACTOR_ID{ int(125) };

			private:
				std::weak_ptr<ctoot::control::BooleanControl> feedbackInvertControl{  };
				std::weak_ptr<ctoot::control::FloatControl> feedbackControl{  };
				std::weak_ptr<ctoot::control::FloatControl> mixControl{  };
				float feedback{  }, mix{ 1.0f };

			protected:
				void derive(ctoot::control::Control* c) override;
				virtual bool isFeedbackInverted();
				virtual std::shared_ptr<ctoot::control::BooleanControl> createFeedbackInvertControl();
				virtual std::shared_ptr<ctoot::control::FloatControl> createFeedbackControl();
				virtual std::shared_ptr<ctoot::control::FloatControl> createMixControl();
				virtual std::shared_ptr<ctoot::control::ControlColumn> createCommonControlColumn(bool withInverts);

			public:
				virtual float getFeedback();
				virtual float getMix();

			public:
				AbstractDelayControls(int id, std::string name);
			};
		}
	}
}
