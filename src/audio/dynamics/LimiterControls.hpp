#pragma once

#include <audio/dynamics/DynamicsControls.hpp>

#include <memory>

namespace ctoot {

	namespace control {
		class ControlLaw;
	}

	namespace audio {
		namespace dynamics {

			class LimiterControls
				: public DynamicsControls
			{

			private:
				static std::weak_ptr<ctoot::control::ControlLaw> RELEASE_LAW();

			protected:
				virtual ctoot::control::ControlLaw* getRelaseLaw();
				bool hasGainReductionIndicator() override;

			public:
				LimiterControls();

			};
		}
	}
}
