#pragma once

#include <control/CompoundControl.hpp>
#include <synth/modules/oscillator/MultiWaveOscillatorVariables.hpp>

namespace ctoot {

	namespace control {
		class ControlLaw;
		class FloatControl;
		class EnumControl;
	}

	namespace synth {
		namespace modules {
			namespace oscillator {

				class MultiWave;

				class MultiWaveOscillatorControls
					: public ctoot::control::CompoundControl
					, public virtual MultiWaveOscillatorVariables
				{

				public:
					static constexpr int32_t WAVE{ int32_t(0) };
					static constexpr int32_t WIDTH{ int32_t(1) };
					static constexpr int32_t DETUNE{ int32_t(2) };
					static constexpr int32_t OCTAVE{ int32_t(5) };

				private:
					std::weak_ptr<ctoot::control::FloatControl> detuneControl{  };
					std::weak_ptr<ctoot::control::EnumControl> waveControl{  };
					std::weak_ptr<ctoot::control::FloatControl> widthControl{  };
					std::weak_ptr<ctoot::control::EnumControl> octaveControl{  };
					int32_t idOffset{ 0 };
					std::weak_ptr<MultiWave> multiWave;
					float width{  };
					float detuneFactor{  };
					int32_t octave{  };
					bool master{  };

				protected:
					void derive(ctoot::control::Control* c) override;

				private:
					void createControls();

				protected:
					virtual std::shared_ptr<ctoot::control::FloatControl> createDetuneControl();
					virtual std::shared_ptr<ctoot::control::EnumControl> createWaveControl();
					virtual std::shared_ptr<ctoot::control::FloatControl> createWidthControl();
					virtual std::shared_ptr<ctoot::control::EnumControl> createOctaveControl();

				private:
					static std::vector<std::string> octaveArray;
					
				private:
					void deriveSampleRateIndependentVariables();
					void deriveSampleRateDependentVariables();

				protected:
					virtual std::weak_ptr<MultiWave> deriveMultiWave();
					virtual float deriveWidth();
					virtual float deriveDetuneFactor();
					virtual int32_t deriveOctave();

				public:
					std::weak_ptr<MultiWave> getMultiWave() override;
					float getWidth() override;
					float getSyncThreshold() override;
					float getDetuneFactor() override;
					int32_t getOctave() override;
					bool isMaster() override;

					MultiWaveOscillatorControls(int32_t instanceIndex, std::string name, int32_t idOffset, bool master);
					MultiWaveOscillatorControls(int32_t id, int32_t instanceIndex, std::string name, int32_t idOffset, bool master);

				private:
					friend class MultiWaveOscillatorOctaveControl;
					static std::weak_ptr<ctoot::control::ControlLaw> TUNING_LAW();
					static std::weak_ptr<ctoot::control::ControlLaw> WIDTH_LAW();
				};

			}
		}
	}
}
