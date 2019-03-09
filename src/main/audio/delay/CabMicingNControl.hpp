#pragma once

#include <control/EnumControl.hpp>

#include <vector>
#include <string>

#include <any>

namespace ctoot {
	namespace audio {
		namespace delay {

			class CabMicingNControl
				: public ctoot::control::EnumControl
			{

			private:
				static std::vector<std::string> values;

			public:
				std::vector<std::any> getValues() override;

			public:
				CabMicingNControl();
			};

		}
	}
}
