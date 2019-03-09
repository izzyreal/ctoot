#pragma once

#include <audio/dynamics/MidSideDynamicsProcess.hpp>

#include <vector>

namespace ctoot {
	namespace audio {
		namespace dynamics {

			class MidSideDynamicsProcessVariables;

			class MidSideCompressor
				: public MidSideDynamicsProcess
			{

			protected:
				std::vector<float> inverseRatio{  };
				std::vector<float> ratio2 = std::vector<float>(2);
				std::vector<float> inverseThreshold{  };

			protected:
				void cacheProcessVariables() override;
				float function(int32_t i, float value) override;

			public:
				MidSideCompressor(MidSideDynamicsProcessVariables* vars);

			};

		}
	}
}
