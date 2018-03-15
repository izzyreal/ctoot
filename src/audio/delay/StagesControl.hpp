#pragma once

#include <control/EnumControl.hpp>

#include <vector>
#include <string>

#include <boost/any.hpp>

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
				std::vector<boost::any> getValues() override;
				virtual int getStages();

			public:
				StagesControl(int stages);

			};

		}
	}
}
