#pragma once

#include <audio/dynamics/DynamicsControls.hpp>

#include <memory>

namespace ctoot {

	namespace control {
		class ControlLaw;
	}

	namespace audio {
		namespace dynamics {

			class GateControls
				: public DynamicsControls
			{

			private:
				static std::weak_ptr<ctoot::control::ControlLaw> THRESH_LAW();
			
			protected:
				ctoot::control::ControlLaw* getThresholdLaw() override;
				bool hasHold() override;
				bool hasDepth() override;
				bool hasHysteresis() override;

			public:
				GateControls();

			};

		}
	}
}
