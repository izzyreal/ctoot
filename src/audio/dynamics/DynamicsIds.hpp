#pragma once

namespace ctoot {
	namespace audio {
		namespace dynamics {

			class DynamicsIds
			{

			public:
				static constexpr int32_t LIMITER_ID{ int32_t(33) };
				static constexpr int32_t COMPRESSOR_ID{ int32_t(34) };
				static constexpr int32_t EXPANDER_ID{ int32_t(35) };
				static constexpr int32_t GATE_ID{ int32_t(36) };
				static constexpr int32_t DEESSER_ID{ int32_t(37) };
				static constexpr int32_t MULTI_BAND_COMPRESSOR_ID{ int32_t(38) };
				static constexpr int32_t TREMOLO_ID{ int32_t(39) };
				static constexpr int32_t MID_SIDE_COMPRESSOR_ID{ int32_t(40) };
				static constexpr int32_t VARI_MU_COMPRESSOR{ int32_t(41) };
				static constexpr int32_t OPTO_COMPRESSOR{ int32_t(42) };
				static constexpr int32_t BUS_COMPRESSOR{ int32_t(43) };
				static constexpr int32_t MULTI_BAND_IZ_COMPRESSOR_ID{ int32_t(44) };
			};
		}
	}
}

