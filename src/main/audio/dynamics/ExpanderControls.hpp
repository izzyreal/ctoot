#pragma once

#include <audio/dynamics/DynamicsControls.hpp>

#include <memory>

namespace ctoot {

	namespace control {
		class ControlLaw;
	}

	namespace audio {
		namespace dynamics {

			class ExpanderControls
				: public DynamicsControls
			{

			private:
				static std::weak_ptr<ctoot::control::ControlLaw> THRESH_LAW();

			protected:
				std::weak_ptr<ctoot::control::ControlLaw> getThresholdLaw() override;
				bool hasRatio() override;

			public:
				ExpanderControls();
			};
			REGISTER_TYPE(ctoot::audio::dynamics::, ExpanderControls)
		}
	}
}
