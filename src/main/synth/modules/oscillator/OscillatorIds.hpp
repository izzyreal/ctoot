#pragma once

namespace ctoot {
	namespace synth {
		namespace modules {
			namespace oscillator {

				class OscillatorIds
				{

				public:
					static constexpr int32_t OSCILLATOR_BASE_ID{ int32_t(0) };
					static constexpr int32_t WAVE_OSCILLATOR_ID{ int32_t(1) };
					static constexpr int32_t MULTI_WAVE_OSCILLATOR_ID{ int32_t(2) };
					static constexpr int32_t LFO_ID{ int32_t(3) };
					static constexpr int32_t ENHANCED_LFO_ID{ int32_t(4) };
					static constexpr int32_t DUAL_MULTI_WAVE_OSCILLATOR_ID{ int32_t(5) };
					static constexpr int32_t DSF_OSCILLATOR_ID{ int32_t(6) };
					static constexpr int32_t HAMMOND_OSCILLATOR_ID{ int32_t(7) };
					static constexpr int32_t UNISON_ID{ int32_t(31) };

				};

			}
		}
	}
}
