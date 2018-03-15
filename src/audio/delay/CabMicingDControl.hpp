#pragma once

#include <control/EnumControl.hpp>

#include <boost/any.hpp>

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
				std::vector<boost::any> getValues() override;


			public:
				CabMicingDControl();
			};

		}
	}
}
