#pragma once

#include <audio/dynamics/DynamicsProcess.hpp>

namespace ctoot {
	namespace audio {
		namespace dynamics {

			class DynamicsVariables;

			class Compressor
				: public DynamicsProcess
			{

			protected:
				float ratio2{  };
				float inverseThreshold{  };

			protected:
				void cacheProcessVariables() override;
				float function(float value) override;

			public:
				Compressor(DynamicsVariables* vars);
			};

		}
	}
}
