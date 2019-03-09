#pragma once

namespace ctoot {
	namespace synth {
		namespace modules {

			class GlideVariables
			{

			public:
				virtual bool isGlideEnabled() = 0;
				virtual int32_t getGlideMilliseconds() = 0;

			};

		}
	}
}
