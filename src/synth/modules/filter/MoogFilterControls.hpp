#pragma once

#include <synth/modules/filter/FilterControls.hpp>

namespace ctoot {
	namespace synth {
		namespace modules {
			namespace filter {
				class MoogFilterControls
					: public FilterControls
				{

				protected:
					float deriveResonance() override;

				public:
					MoogFilterControls(int32_t instanceIndex, std::string name, int32_t idOffset);

				};

			}
		}
	}
}
