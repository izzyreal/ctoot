#pragma once

#include <vector>

namespace ctoot {
	namespace audio {
		namespace delay {

			class DelayTap;

			class CabMicingProcess_Variables
				
			{
			public:
				virtual bool isBypassed() = 0;
				virtual std::vector<DelayTap*> getTaps() = 0;

			};
		}
	}
}
