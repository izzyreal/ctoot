#pragma once

#include <control/EnumControl.hpp>

#include <vector>
#include <string>

#include <any>

namespace ctoot {
	namespace audio {
		namespace delay {

			class StagesControl
				: public ctoot::control::EnumControl
			{

			public:
				typedef ctoot::control::EnumControl super;

			private:
				static std::vector<std::string> values;

			public:
				std::vector<std::any> getValues() override;
				virtual int getStages();

			public:
				StagesControl(int stages);

			};

		}
	}
}
