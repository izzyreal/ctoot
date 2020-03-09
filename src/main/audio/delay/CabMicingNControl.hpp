#pragma once

#include <control/EnumControl.hpp>

#include <vector>
#include <string>

#include <thirdp/any.hpp>

namespace ctoot {
	namespace audio {
		namespace delay {

			class CabMicingNControl
				: public ctoot::control::EnumControl
			{

			private:
				static std::vector<std::string> values;

			public:
				std::vector<nonstd::any> getValues() override;

			public:
				CabMicingNControl();
			};

		}
	}
}
