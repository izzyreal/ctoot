#pragma once

#include <audio/dynamics/DynamicsProcess.hpp>

namespace ctoot {
	namespace audio {
		namespace dynamics {

			class DynamicsVariables;

			class Gate
				: public DynamicsProcess
			{

			private:
				int32_t holdCount{ 0 };
				int32_t hold{  };
				bool open_{ false };
				float depth{  };
				float hysteresis{  };

			protected:
				void cacheProcessVariables() override;
				float function(float value) override;

			public:
				Gate(DynamicsVariables* vars);

			};

		}
	}
}
