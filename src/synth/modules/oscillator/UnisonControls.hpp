#pragma once

#include <control/CompoundControl.hpp>
#include <synth/modules/oscillator/UnisonVariables.hpp>

namespace ctoot {
	namespace synth {
		namespace modules {
			namespace oscillator {

				class UnisonControls
					: public ctoot::control::CompoundControl
					, public virtual UnisonVariables
				{

				public:
					static constexpr int32_t OSC_COUNT{ int32_t(0) };
					static constexpr int32_t PITCH_SPREAD{ int32_t(1) };
					static constexpr int32_t PHASE_SPREAD{ int32_t(2) };

				private:
					static ctoot::control::IntegerLaw* OSC_COUNT_LAW_;
					static ctoot::control::LinearLaw* SPREAD_LAW_;
					ctoot::control::IntegerControl* oscillatorCountControl{  };
					ctoot::control::FloatControl* pitchSpreadControl{  };
					ctoot::control::FloatControl* phaseSpreadControl{  };
					int32_t idOffset{  };
					int32_t oscillatorCount{  };
					float pitchSpread{  };
					float phaseSpread{  };

				protected:
					void derive(ctoot::control::Control* c) override;

				private:
					void createControls();

				protected:
					virtual ctoot::control::IntegerControl* createOscillatorCountControl();
					virtual ctoot::control::FloatControl* createPitchSpreadControl();
					virtual ctoot::control::FloatControl* createPhaseSpreadControl();

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

				private:
					static ctoot::control::IntegerLaw*& OSC_COUNT_LAW();
					static ctoot::control::LinearLaw*& SPREAD_LAW();

				};

			}
		}
	}
}
