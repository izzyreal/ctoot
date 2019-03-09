#pragma once

#include <synth/modules/filter/AbstractSynthFilter.hpp>

namespace ctoot {
	namespace synth {
		namespace modules {
			namespace filter {

				class DualStateVariableFilterVariables;
				class DualStateVariableFilterElement;
				class DualStateVariableFilterConfig;

				class DualStateVariableFilter
					: public AbstractFilter
				{

				private:
					DualStateVariableFilterElement* element{  };
					DualStateVariableFilterConfig* config{  };
					float res{  };

				public:
					virtual float update();
					virtual float filter(float sample, float fn1);

					DualStateVariableFilter(DualStateVariableFilterVariables* variables);
					~DualStateVariableFilter();
				};

			}
		}
	}
}
