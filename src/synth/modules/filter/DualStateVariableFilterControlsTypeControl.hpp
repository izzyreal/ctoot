#pragma once

#include <control/EnumControl.hpp>

#include <boost/any.hpp>

#include <vector>

namespace ctoot {
	namespace synth {
		namespace modules {
			namespace filter {

				class DualStateVariableFilterControlsTypeControl
					: public ctoot::control::EnumControl
				{

				private:
					std::vector<boost::any> values{  };

				private:
					void createValues();

				public:
					std::vector<boost::any> getValues() override;
					int32_t getWidthLimit() override;

					DualStateVariableFilterControlsTypeControl(int32_t id, std::string name);

				};

			}
		}
	}
}
