#pragma once

#include <control/FloatControl.hpp>

#include <memory>

namespace ctoot {

	namespace control {
		class LinearLaw;
	}

	namespace audio {
		namespace dynamics {

			class GainReductionIndicator
				: public ctoot::control::FloatControl
			{

			private:
				static std::weak_ptr<ctoot::control::LinearLaw> GR_LAW();

			public:
				GainReductionIndicator();
			};

		}
	}
}
