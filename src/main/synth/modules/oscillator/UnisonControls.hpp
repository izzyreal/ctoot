#pragma once

#include <control/CompoundControl.hpp>
#include <synth/modules/oscillator/UnisonVariables.hpp>

#include <memory>

namespace ctoot {

	namespace control {
		class FloatControl;
		class IntegerControl;
		class LinearLaw;
		class IntegerLaw;
	}

	namespace synth {
		namespace modules {
			namespace oscillator {

				class UnisonControls
					: public ctoot::control::CompoundControl
					, public virtual UnisonVariables
				{

				public:
					static constexpr int32_t OSC_COUNT{ 0 };
					static constexpr int32_t PITCH_SPREAD{ 1 };
					static constexpr int32_t PHASE_SPREAD{ 2 };

				private:
					static std::weak_ptr<ctoot::control::IntegerLaw> OSC_COUNT_LAW();
					static std::weak_ptr<ctoot::control::LinearLaw> SPREAD_LAW();
					std::weak_ptr<ctoot::control::IntegerControl> oscillatorCountControl{  };
					std::weak_ptr<ctoot::control::FloatControl> pitchSpreadControl{  };
					std::weak_ptr<ctoot::control::FloatControl> phaseSpreadControl{  };
					int32_t idOffset{  };
					int32_t oscillatorCount{  };
					float pitchSpread{  };
					float phaseSpread{  };

				protected:
					void derive(ctoot::control::Control* c) override;

				private:
					void createControls();

				protected:
					virtual std::shared_ptr<ctoot::control::IntegerControl> createOscillatorCountControl();
					virtual std::shared_ptr<ctoot::control::FloatControl> createPitchSpreadControl();
					virtual std::shared_ptr<ctoot::control::FloatControl> createPhaseSpreadControl();

				private:
					void deriveSampleRateIndependentVariables();

				protected:
					virtual int32_t deriveOscillatorCount();
					virtual float derivePitchSpread();
					virtual float derivePhaseSpread();

				public:
					int32_t getOscillatorCount() override;
					float getPitchSpread() override;
					float getPhaseSpread() override;

					UnisonControls(int32_t idOffset);

				};

			}
		}
	}
}
