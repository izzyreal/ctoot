#pragma once

namespace ctoot {
	namespace synth {
		namespace modules {
			namespace filter {

				class DualStateVariableFilterConfig;

				class DualStateVariableFilterElement
				{

				private:
					float prev{ 0.0f };
					float low1{  }, high1{  }, band1{  }, notch1{  };

				public:
					float low{  }, high{  }, band{  }, notch{  };
					virtual float filter(float in, DualStateVariableFilterConfig* config);

					DualStateVariableFilterElement();

				};

			}
		}
	}
}
