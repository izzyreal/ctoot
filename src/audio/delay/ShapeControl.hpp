#pragma once

#include <control/EnumControl.hpp>

#include <string>
#include <vector>

#include <boost/any.hpp>

namespace ctoot {
	namespace audio {
		namespace delay {

			class ShapeControl
				: public ctoot::control::EnumControl
			{
			private:
				static std::vector<std::string> values;

			public:
				std::vector<boost::any> getValues() override;
				bool hasLabel() override;

			public:
				ShapeControl(int id);

			};

		}
	}
}
