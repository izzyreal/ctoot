#pragma once

#include <audio/dynamics/ClassicDynamicsProcess.hpp>

namespace ctoot {
	namespace audio {
		namespace dynamics {

			class BusCompressor
				: public ClassicDynamicsProcess
			{

			protected:
				float inverseRatio{  }, oneMinusInverseRatio{  };
				float kneedB{  }, halfInverseKneedB{  };
				float thresholddB{  }, thresholdMinusKneedB{  }, thresholdPlusKneedB{  };

			private:
				float y1{  }, y2{  };
				float m1{  }, m2{  };

			protected:
				void cacheProcessVariables() override;
				virtual void deriveLocalVariables();
				float function(float value) override;
				float dynamics(float target) override;

			public:
				BusCompressor(DynamicsVariables* vars);

			};

		}
	}
}
