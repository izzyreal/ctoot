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
				virtual ctoot::control::ControlLaw* getReleaseLaw() override;
				bool hasGainReductionIndicator() override;

			public:
				LimiterControls();

			};
			REGISTER_TYPE(ctoot::audio::dynamics::, LimiterControls)
		}
	}
}
