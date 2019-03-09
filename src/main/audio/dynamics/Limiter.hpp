#pragma once

#include <audio/dynamics/DynamicsProcess.hpp>

namespace ctoot {
	namespace audio {
		namespace dynamics {

			class Limiter
				: public DynamicsProcess
			{

			protected:
				float function(float value) override;

			public:
				Limiter(DynamicsVariables* vars);
			};

		}
	}
}
