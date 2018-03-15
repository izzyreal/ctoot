#pragma once

#include <control/CompoundControl.hpp>
#include <control/FloatControl.hpp>
#include <audio/delay/DelayTap.hpp>

namespace ctoot {
	namespace audio {
		namespace delay {

			class DelayTapControls
				: public ctoot::control::CompoundControl
				, public virtual DelayTap
			{

			public:
				typedef ctoot::control::CompoundControl super;

			private:
				std::weak_ptr<ctoot::control::FloatControl> delayControl{  };
				std::weak_ptr<ctoot::control::FloatControl> levelControl{  };

			public:
				bool isAlwaysVertical() override;
				float getDelayMilliseconds() override;
				float getLevel() override;

			public:				
				DelayTapControls(int id, std::weak_ptr<ctoot::control::ControlLaw> law);

			};

		}
	}
}
