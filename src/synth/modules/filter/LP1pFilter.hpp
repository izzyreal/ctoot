#pragma once

namespace ctoot {
	namespace synth {
		namespace modules {
			namespace filter {

				class LP1pFilter
				{

				private:
					float y1{ 0.0f };
					float g{  };

				public:
					virtual float filter(float sample);

					LP1pFilter(float freq, int32_t rate);

				};

			}
		}
	}
}
