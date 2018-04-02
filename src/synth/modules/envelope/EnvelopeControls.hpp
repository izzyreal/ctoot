#pragma once

#include <control/CompoundControl.hpp>

#include <synth/modules/envelope/EnvelopeVariables.hpp>

#include <memory>

namespace ctoot {

	namespace control {
		class FloatControl;
		class ControlLaw;
	}

	namespace synth {
		namespace modules {
			namespace envelope {
				class EnvelopeControls
					: public ctoot::control::CompoundControl
					, public virtual EnvelopeVariables
				{
				private:
					static float LOG_0_01;
					static std::vector<std::shared_ptr<ctoot::control::ControlLaw>> laws;

				private:
					std::weak_ptr<ctoot::control::FloatControl> delayControl{  };
					std::weak_ptr<ctoot::control::FloatControl> attackControl{  };
					std::weak_ptr<ctoot::control::FloatControl> holdControl{  };
					std::weak_ptr<ctoot::control::FloatControl> decayControl{  };
					std::weak_ptr<ctoot::control::FloatControl> sustainControl{  };
					std::weak_ptr<ctoot::control::FloatControl> releaseControl{  };
					int32_t sampleRate{ 44100 };
					int32_t delay{ 0 }, hold{  };
					float attack{  }, decay{  }, sustain{  }, release{  };
					int32_t idOffset{ 0 };
					bool hasDelay{  };
					bool hasHold{  };
					bool hasSustain{  };
					float timeMultiplier{  };

				protected:
					void derive(ctoot::control::Control* c) override;
					virtual void createControls();
					virtual void deriveSampleRateIndependentVariables();
					virtual void deriveSampleRateDependentVariables();

				protected:
					virtual float deriveTimeFactor(float milliseconds);
					virtual int32_t deriveDelay();
					virtual float deriveAttack();
					virtual int32_t deriveHold();
					virtual float deriveDecay();
					virtual float deriveSustain();
					virtual float deriveRelease();
					virtual std::shared_ptr<ctoot::control::FloatControl> createDelayControl(float min, float max, float init_);
					virtual std::shared_ptr<ctoot::control::FloatControl> createAttackControl(float min, float max, float init_);
					virtual std::shared_ptr<ctoot::control::FloatControl> createHoldControl(float min, float max, float init_);
					virtual std::shared_ptr<ctoot::control::FloatControl> createDecayControl(float min, float max, float init_);
					virtual std::shared_ptr<ctoot::control::FloatControl> createSustainControl();
					virtual std::shared_ptr<ctoot::control::FloatControl> createReleaseControl(float min, float max, float init_);

				public:
					int32_t getDelayCount() override;
					float getAttackCoeff() override;
					int32_t getHoldCount() override;
					float getDecayCoeff() override;
					float getSustainLevel() override;
					float getReleaseCoeff() override;
					void setSampleRate(int32_t rate) override;

					EnvelopeControls(int32_t instanceIndex, std::string name, int32_t idOffset);
					EnvelopeControls(int32_t instanceIndex, std::string name, int32_t idOffset, std::string options);
					EnvelopeControls(int32_t instanceIndex, std::string name, int32_t idOffset, std::string options, float timeMultiplier);
					EnvelopeControls(int32_t id, int32_t instanceIndex, std::string name, int32_t idOffset, std::string options, float timeMultiplier);
				};

			}
		}
	}
}
