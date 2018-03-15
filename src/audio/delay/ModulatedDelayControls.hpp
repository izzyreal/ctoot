#pragma once

#include <audio/delay/AbstractDelayControls.hpp>
#include <audio/delay/ModulatedDelayProcessVariables.hpp>

#include <string>

namespace ctoot {
	namespace audio {
		namespace delay {

			class ShapeControl;

			class ModulatedDelayControls
				: public AbstractDelayControls
				, public virtual ModulatedDelayProcessVariables
			{

			public:
				typedef AbstractDelayControls super;

			private:
				static constexpr float HALF_ROOT_2{ 0.707f };
				static std::weak_ptr<ctoot::control::ControlLaw> DELAY_LAW();
				static std::weak_ptr<ctoot::control::ControlLaw> RATE_LAW();
				std::weak_ptr<ctoot::control::FloatControl> dryControl;
				std::weak_ptr<ctoot::control::FloatControl> wetControl;
				std::weak_ptr<ctoot::control::FloatControl> delayControl;
				std::weak_ptr<ctoot::control::FloatControl> rateControl;
				std::weak_ptr<ShapeControl> shapeControl;
				std::weak_ptr<ctoot::control::FloatControl> depthControl;
				std::weak_ptr<ctoot::control::BooleanControl> phaseControl;
				float dry{  }, wet{  }, delay{  }, rate{  }, depth{  };
				int shape{  };
				bool quadrature{  };
				static constexpr int DRY_ID{ int(0) };
				static constexpr int DELAY_ID{ int(1) };
				static constexpr int RATE_ID{ int(3) };
				static constexpr int SHAPE_ID{ int(4) };
				static constexpr int DEPTH_ID{ int(5) };

			protected:
				static constexpr int PHASE_ID{ int(7) };
			
			public:
				void derive(ctoot::control::Control* c) override;
				
			public:
				virtual std::shared_ptr<ctoot::control::ControlColumn> createControlColumn1();

			public:
				float getMaxDelayMilliseconds() override;
				float getDelayMilliseconds() override;
				float getRate() override;
				float getDepth() override;
				float getDry() override;
				float getWet() override;
				int getLFOShape() override;
				bool isPhaseQuadrature() override;

			public:
				ModulatedDelayControls();
				ModulatedDelayControls(int id, std::string name);

			public:				
				virtual bool isBypassed();
				virtual float getFeedback();
			};
			REGISTER_TYPE(ctoot::audio::delay::, ModulatedDelayControls)
		}
	}
}
