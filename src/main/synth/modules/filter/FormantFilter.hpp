#pragma once

#include <vector>
#include <stdint.h>

namespace ctoot {
	namespace synth {
		namespace modules {
			namespace filter {

				class FormantFilterVariables;
				class StateVariableFilterElement;

				class FormantFilter
				{

				private:
					FormantFilterVariables* vars{  };
					std::vector<StateVariableFilterElement*> filters;
					std::vector<float> fn{  };
					std::vector<float> level{  };
					float res{  };
					int32_t nBands{  };

				public:
					virtual float filter(float sample);
					virtual void setSampleRate(int32_t rate);
					virtual void update();

					FormantFilter(FormantFilterVariables* vars);

				};

			}
		}
	}
}
