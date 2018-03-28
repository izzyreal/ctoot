#pragma once

namespace ctoot {
	namespace synth {
		namespace modules {
			namespace oscillator {

				class LFOConfig
				{

				public:
					float rateMin{  };
					float rateMax{  };
					float rate{  };
					float deviationMax{  };
					float deviation{  };

					LFOConfig();

				private:
					void init();
				};

			}
		}
	}
}
