#pragma once

#include <control/FloatControl.hpp>

#include <string>

namespace ctoot {
	namespace audio {
		namespace meter {

			class MeterIndicator
				: public ctoot::control::FloatControl
			{

			public:
				MeterIndicator(std::string name);

			};

		}
	}
}
