#pragma once

#include <control/BooleanControl.hpp>

namespace ctoot {
	namespace audio {
		namespace meter {

			class MeterControls;

			class ResetControl
				: public ctoot::control::BooleanControl
			{

			public:
				void momentaryAction() override;
				int32_t getWidthLimit() override;

				ResetControl(MeterControls* mcThis);


			public:
				MeterControls* mcThis;

			private:
				friend class MeterControls;
				friend class ChannelState;
				friend class TypeControl;
				friend class OverIndicator;
				friend class MindBControl;
				friend class MeterIndicator;
			};

		}
	}
}
