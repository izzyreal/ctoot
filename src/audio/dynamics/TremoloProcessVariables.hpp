#pragma once

namespace ctoot {
	namespace audio {
		namespace dynamics {

			class TremoloProcessVariables
			{
			public:
				virtual bool isBypassed() = 0;
				virtual float getDepth() = 0;
				virtual float getRate() = 0;
			};

		}
	}
}
