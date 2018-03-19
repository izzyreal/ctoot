#pragma once

#include <audio/dynamics/ClassicDynamicsProcess.hpp>

namespace ctoot {
	namespace audio {
		namespace dynamics {

			class VariMuCompressor
				: public ClassicDynamicsProcess
			{

			protected:
				float function(float value) override;

			private:
				static std::vector<float> table;

			public:
				VariMuCompressor(DynamicsVariables* vars);

			};

		}
	}
}
