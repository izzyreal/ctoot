#pragma once

#include <control/CompoundControl.hpp>
#include <synth/modules/filter/FormantFilterVariables.hpp>

#include <vector>
#include <memory>

namespace ctoot {

	namespace control {
		class ControlLaw;
		class BooleanControl;
		class FloatControl;
	}

	namespace synth {
		namespace modules {
			namespace filter {
				class FormantFilterControls
					: public ctoot::control::CompoundControl
					, public virtual FormantFilterVariables
				{

				private:
					static ctoot::control::ControlLaw* FREQ_LAW_;
					static ctoot::control::ControlLaw* SHIFT_LAW_;
					static constexpr int32_t RESONANCE{ 0 };
					static constexpr int32_t FREQSHIFT{ 1 };
					static constexpr int32_t FREQUENCY{ 2 };
					static constexpr int32_t LEVEL{ 3 };
					static constexpr int32_t ENABLE{ 15 };
					std::vector<std::weak_ptr<ctoot::control::FloatControl>> frequencyControl{  };
					std::vector<std::weak_ptr<ctoot::control::FloatControl>> levelControl{  };
					std::weak_ptr<ctoot::control::FloatControl> frequencyShiftControl{  };
					std::weak_ptr<ctoot::control::FloatControl> resonanceControl{  };
					std::weak_ptr<ctoot::control::BooleanControl> enableControl{  };
					std::vector<float> frequency{  };
					std::vector<float> level{  };
					float frequencyShift{  };
					float resonance{  };
					bool bypass{  };

				protected:
					int32_t idOffset{ 0 };

				private:
					int32_t sampleRate{ 44100 };
					int32_t nBands{ 4 };
				
				protected:
					void derive(ctoot::control::Control* c) override;
					virtual void createControls();
					virtual void deriveSampleRateIndependentVariables();
					virtual void deriveSampleRateDependentVariables();
					virtual float deriveFrequency(int32_t n);
					virtual float deriveLevel(int32_t n);
					virtual float deriveResonance();
					virtual float deriveFrequencyShift();
					virtual bool deriveEnable();
					virtual std::shared_ptr<ctoot::control::FloatControl> createFrequencyControl(int32_t n);
					virtual std::shared_ptr<ctoot::control::FloatControl> createLevelControl(int32_t n);
					virtual std::shared_ptr<ctoot::control::FloatControl> createResonanceControl();
					virtual std::shared_ptr<ctoot::control::FloatControl> createFrequencyShiftControl();
					virtual std::shared_ptr<ctoot::control::BooleanControl> createPowerControl();

				public:
					void setSampleRate(int32_t rate) override;
					float getFreqencyShift() override;
					float getFrequency(int32_t n) override;
					float getLevel(int32_t n) override;
					float getResonance() override;
					bool isBypassed() override;
					int32_t size() override;

					FormantFilterControls(int32_t instanceIndex, std::string name, int32_t idOffset);

				private:
					static std::weak_ptr<ctoot::control::ControlLaw> FREQ_LAW();
					static std::weak_ptr<ctoot::control::ControlLaw> SHIFT_LAW();
				};

			}
		}
	}
}
