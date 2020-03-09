#pragma once

#include <control/EnumControl.hpp>

#include <thirdp/any.hpp>

#include <string>
#include <vector>

namespace ctoot {
	namespace audio {
		namespace delay {

			class DelayTap;
			
			class CabMicingDControl
				: public ctoot::control::EnumControl
			{

			public:
				typedef ctoot::control::EnumControl super;

			private:
				static std::vector<std::string> values;
			
			public:
				std::vector<nonstd::any> getValues() override;


			public:
				CabMicingDControl();
			};

		}
	}
}
