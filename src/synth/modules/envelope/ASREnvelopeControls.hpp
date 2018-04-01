#pragma once

#include <control/CompoundControl.hpp>
#include <synth/modules/envelope/ASREnvelopeVariables.hpp>

namespace ctoot {

	namespace control {
		class FloatControl;
		class BooleanControl;
	}

	namespace synth {
		namespace modules {
			namespace envelope {

				class ASREnvelopeControls
					: public ctoot::control::CompoundControl
					, public virtual ASREnvelopeVariables
				{

				private:
					std::weak_ptr<ctoot::control::FloatControl> attackControl{  };
					std::weak_ptr<ctoot::control::BooleanControl> sustainControl{  };
					std::weak_ptr<ctoot::control::FloatControl> releaseControl{  };
					int32_t sampleRate{ 44100 };
					float attack{  }, release{  };
					bool sustain{  };
					int32_t idOffset{ 0 };
					float timeMultiplier{  };

				protected:
					void derive(ctoot::control::Control* c) override;
					virtual bool hasDelay();
					virtual void createControls();
					virtual void deriveSampleRateIndependentVariables();
					virtual void deriveSampleRateDependentVariables();
					virtual bool deriveSustain();

				private:
					static float LOG_0_01;

				protected:
					virtual float deriveTimeFactor(float milliseconds);
					virtual float deriveAttack();
					virtual float deriveRelease();
					virtual std::shared_ptr<ctoot::control::FloatControl> createAttackControl(float min, float max, float init_);
					virtual std::shared_ptr<ctoot::control::BooleanControl> createSustainControl();
					virtual std::shared_ptr<ctoot::control::FloatControl> createReleaseControl(float min, float max, float init_);

				public:
					float getAttackCoeff() override;
					bool getSustain() override;
					float getReleaseCoeff() override;
					void setSampleRate(int32_t rate) override;

					ASREnvelopeControls(int32_t instanceIndex, std::string name, int32_t idOffset);
					ASREnvelopeControls(int32_t instanceIndex, std::string name, int32_t idOffset, float timeMultiplier);
					ASREnvelopeControls(int32_t id, int32_t instanceIndex, std::string name, int32_t idOffset, float timeMultiplier);

				};

			}
		}
	}
}
