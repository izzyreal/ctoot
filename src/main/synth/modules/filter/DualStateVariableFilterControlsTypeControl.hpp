#pragma once

#include <control/EnumControl.hpp>

#include <any>

#include <vector>

namespace ctoot {
	namespace synth {
		namespace modules {
			namespace filter {

				class DualStateVariableFilterControlsTypeControl
					: public ctoot::control::EnumControl
				{

				private:
					std::vector<std::any> values{  };

				private:
					void createValues();

				public:
					std::vector<std::any> getValues() override;
					int32_t getWidthLimit() override;

					DualStateVariableFilterControlsTypeControl(int32_t id, std::string name);

				};

			}
		}
	}
}
