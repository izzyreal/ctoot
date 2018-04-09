#pragma once

#include <audio/dynamics/izcompressor/IzCompressorProcess.hpp>

#include <vector>

namespace ctoot {
	namespace audio {
		namespace dynamics {
			namespace izcompressor {

				class IzCompressorProcessVariables;

				class IzCompressor
					: public IzCompressorProcess
				{

				protected:
					float inverseRatio;
					float ratio;
					float inverseThreshold;

				protected:
					void cacheProcessVariables() override;
					float function(float value) override;

				public:
					IzCompressor(IzCompressorProcessVariables* vars);

				};

			}
		}
	}
}
