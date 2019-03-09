#pragma once

namespace ctoot {
	namespace synth {
		namespace modules {
			namespace filter {

				class LP1pHP1pVariables
				{
				public:
					virtual float getHighPassRatio() = 0;
					virtual float getLowPassRatio() = 0;

				};

			}
		}
	}
}
