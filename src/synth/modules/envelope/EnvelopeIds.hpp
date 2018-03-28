#pragma once

#include <cstdint>

namespace ctoot {
	namespace synth {
		namespace modules {
			namespace envelope {

				class EnvelopeIds
				{

				public:
					static constexpr int32_t ENVELOPE_BASE_ID{ int32_t(64) };
					static constexpr int32_t DAHDSR_ENVELOPE_ID{ int32_t(65) };

				};

			}
		}
	}
}
