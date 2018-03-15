#pragma once

#include <audio/delay/AbstractDelayControls.hpp>
#include <audio/delay/MultiTapDelayProcessVariables.hpp>
#include <audio/delay/MultiTapDelayControls.hpp>

#include <vector>

namespace ctoot {
	namespace audio {
		namespace delay {

			class MultiTapDelayStereoControls
				: public AbstractDelayControls
				, public virtual MultiTapDelayProcessVariables
			{

			private:
				std::vector<std::weak_ptr<MultiTapDelayControls>> perChannelControls;
				float msMax{  };
				static std::weak_ptr<ctoot::control::ControlLaw> DELAY_FACTOR_LAW();
				std::weak_ptr<ctoot::control::FloatControl> delayFactorControl;
				float delay{  };

			public:
				void derive(ctoot::control::Control* c) override;

			public:
				float getMaxDelayMilliseconds() override;
				std::vector<std::weak_ptr<DelayTap>> getTaps(int chan) override;
				int getChannelCount() override;
				float getDelayFactor() override;

			public:
				MultiTapDelayStereoControls();
				MultiTapDelayStereoControls(int ntaps, float ms);

			public:
				virtual bool isBypassed();
				virtual float getFeedback();
				virtual float getMix();

			};
			REGISTER_TYPE(ctoot::audio::delay::, MultiTapDelayStereoControls)
		}
	}
}
