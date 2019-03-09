#pragma once

#include <synth/modules/filter/AbstractSynthFilter.hpp>

namespace ctoot {
	namespace synth {
		namespace modules {
			namespace filter {

				class MoogFilterElement;

				class MoogFilter2
					: public AbstractFilter
				{

				private:
					MoogFilterElement * element{  };
					float res{  };

				public:
					virtual float update();
					virtual float filter(float sample, float f);

					MoogFilter2(FilterVariables* variables);

				};

			}
		}
	}
}

