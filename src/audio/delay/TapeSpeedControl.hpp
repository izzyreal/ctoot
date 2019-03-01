#pragma once

#include <control/EnumControl.hpp>

#include <any>

namespace ctoot {
	namespace audio {
		namespace delay {

			class WowFlutterControls;

			class TapeSpeedControl
				: public ctoot::control::EnumControl
			{


			public:
				std::vector<std::any> getValues() override;
				bool hasLabel() override;

			public:
				TapeSpeedControl(WowFlutterControls *WowFlutterControls_this);
				WowFlutterControls *WowFlutterControls_this;

			};

		}
	}
}
