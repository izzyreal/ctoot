#pragma once

#include <synth/modules/filter/FilterVariables.hpp>

namespace ctoot {
	namespace synth {
		namespace  modules {
			namespace filter {

				class DualStateVariableFilterConfig;

				class DualStateVariableFilterVariables
					: public virtual FilterVariables
				{

				public:
					virtual DualStateVariableFilterConfig* getType() = 0;

				};
			}
		}
	}
}
