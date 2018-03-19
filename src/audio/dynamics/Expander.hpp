#pragma once

#include <audio/dynamics/DynamicsProcess.hpp>

namespace ctoot {
	namespace audio {
		namespace dynamics {

			class Expander
				: public DynamicsProcess
			{

			protected:
				float function(float value) override;

			public:
				Expander(DynamicsVariables* vars);

			};

		}
	}
}
