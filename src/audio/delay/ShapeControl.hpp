#pragma once

#include <control/EnumControl.hpp>

#include <string>
#include <vector>

#include <any>

namespace ctoot {
	namespace audio {
		namespace delay {

			class ShapeControl
				: public ctoot::control::EnumControl
			{
			private:
				static std::vector<std::string> values;

			public:
				std::vector<std::any> getValues() override;
				bool hasLabel() override;

			public:
				ShapeControl(int id);

			};

		}
	}
}
