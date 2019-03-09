#pragma once

#include <string>

namespace ctoot {
	namespace synth {
		namespace modules {
			namespace filter {
				class DualStateVariableFilterConfig
				{

				private:
					std::string name{  };

				public:
					int32_t type1{  };
					int32_t type2{  };
					int32_t f2ratio{  };
					float freq1{  };
					float freq2{  };
					float damp1{  };
					float damp2{  };
					std::string toString();

					DualStateVariableFilterConfig(std::string name, int32_t t1, int32_t t2, int32_t ratio);

				};

			}
		}
	}
}
