#pragma once
#include <control/CompoundControl.hpp>
#include <synth/modules/oscillator/DSFOscillatorVariables.hpp>

#include <memory>

namespace ctoot {

	namespace control {
		class IntegerLaw;
		class IntegerControl;
		class FloatControl;
		class BooleanControl;
	}

	namespace synth {
		namespace modules {
			namespace oscillator {

				class DSFOscillatorControls
					: public ctoot::control::CompoundControl
					, public virtual DSFOscillatorVariables
				{

				public:
					static constexpr int32_t RATIO_N{ int32_t(0) };
					static constexpr int32_t RATIO_D{ int32_t(1) };
					static constexpr int32_t PARTIALS{ int32_t(2) };
					static constexpr int32_t ROLLOFF{ int32_t(3) };
					static constexpr int32_t WOLFRAM{ int32_t(4) };

				private:
					std::weak_ptr<ctoot::control::IntegerControl> ratioNumeratorControl{  };
					std::weak_ptr<ctoot::control::IntegerControl> ratioDenominatorControl{  };
					std::weak_ptr<ctoot::control::IntegerControl> partialsControl{  };
					std::weak_ptr<ctoot::control::FloatControl> rolloffControl{  };
					std::weak_ptr<ctoot::control::BooleanControl> wolframControl{  };
					int32_t idOffset{  };
					int32_t ratioNumerator{  };
					int32_t ratioDenominator{  };
					int32_t partialCount{  };
					float rolloffFactor{  };
					int32_t rolloffInt{  };
					bool canUseWolfram_{  };

				protected:
					void derive(ctoot::control::Control* c) override;

				private:
					void createControls();

				protected:
					virtual std::shared_ptr<ctoot::control::IntegerControl> createRatioControl(int32_t id, std::string name);
					virtual std::shared_ptr<ctoot::control::IntegerControl> createPartialsControl(int32_t id);
					virtual std::shared_ptr<ctoot::control::FloatControl> createRolloffControl(int32_t id);
					virtual std::shared_ptr<ctoot::control::BooleanControl> createWolframControl(int32_t id);

				private:
					void deriveSampleRateIndependentVariables();

				protected:
					virtual int32_t deriveRatioDenominator();
					virtual int32_t deriveRatioNumerator();
					virtual int32_t derivePartialCount();
					virtual float deriveRolloffFactor();
					virtual int32_t deriveRolloffInt();
					virtual bool deriveWolfram();

				public:
					int32_t getPartialCount() override;
					float getPartialRolloffFactor() override;
					int32_t getPartialRolloffInt() override;
					int32_t getRatioDenominator() override;
					int32_t getRatioNumerator() override;
					bool canUseWolfram() override;

					DSFOscillatorControls(int32_t instanceIndex, std::string name, int32_t idOffset);

				private:
					static std::weak_ptr<ctoot::control::IntegerLaw> RATIO_LAW();
					static std::weak_ptr<ctoot::control::IntegerLaw> PARTIAL_LAW();
				};

			}
		}
	}
}
