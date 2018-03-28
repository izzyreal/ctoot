#pragma once

namespace ctoot {
	namespace synth {
		namespace modules {
			namespace filter {
				class MoogFilterElement
				{

				private:
					double in1{  }, in2{  }, in3{  }, in4{  }, out1{  }, out2{  }, out3{  }, out4{  };

				public:
					virtual float filter(float input, float fc, float res);

				};

			}
		}
	}
}
