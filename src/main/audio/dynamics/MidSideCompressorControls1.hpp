#pragma once
#include <audio/dynamics/CompressorControls.hpp>

#include <string>

namespace ctoot {
	namespace audio {
		namespace dynamics {

			class MidSideCompressorControls1
				: public CompressorControls
			{

			protected:
				bool hasKey() override;

			public:
				bool canBypass() override;

			public:
				MidSideCompressorControls1(std::string name, int32_t idOffset);

			};
		}
	}
}
