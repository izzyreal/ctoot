#pragma once

#include <control/EnumControl.hpp>

namespace ctoot {
	namespace synth {
		namespace modules {
			namespace oscillator {

				class ShapeControl
					: public ctoot::control::EnumControl
				{

				public:
					std::vector<boost::any> getValues() override;

					ShapeControl(int32_t id, std::string name, boost::any value);

				};

			}
		}
	}
}
