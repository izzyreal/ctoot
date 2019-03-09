#pragma once

#include <control/CompoundControl.hpp>
#include <synth/modules/oscillator/LFOVariables.hpp>

#include <memory>

namespace ctoot {

	namespace control {
		class EnumControl;
		class ControlLaw;
		class FloatControl;
	}

	namespace synth {
		namespace modules {
			namespace oscillator {

				class LFOConfig;

				class LFOControls
					: public ctoot::control::CompoundControl
					, public virtual LFOVariables
				{
				private:
					static std::vector<std::shared_ptr<ctoot::control::ControlLaw>> laws;

				public:
					static constexpr int32_t FREQUENCY{ 0 };
					static constexpr int32_t DEVIATION{ 1 };
					static constexpr int32_t SHAPE{ 2 };

				private:
					std::weak_ptr<ctoot::control::FloatControl> frequencyControl{  };
					std::weak_ptr<ctoot::control::FloatControl> deviationControl{  };
					std::weak_ptr<ctoot::control::EnumControl> shapeControl{  };

				protected:
					int32_t idOffset{  };

				private:
					float frequency{  }, deviation{  };
					bool sine{  };

				protected:
					LFOConfig * config{  };

				protected:
					void derive(ctoot::control::Control* c) override;
					virtual void createControls();
					virtual std::shared_ptr<ctoot::control::EnumControl> createShapeControl();
					virtual std::shared_ptr<ctoot::control::FloatControl> createFrequencyControl();
					virtual std::shared_ptr<ctoot::control::FloatControl> createDeviationControl();
					virtual void deriveSampleRateIndependentVariables();
					virtual void deriveSampleRateDependentVariables();
					virtual float deriveFrequency();
					virtual float deriveDeviation();
					virtual bool deriveShape();

				public:
					float getFrequency() override;
					float getDeviation() override;
					bool isSine() override;

					LFOControls(int32_t instanceIndex, std::string name, int32_t idOffset, LFOConfig* cfg);
					LFOControls(int32_t id, int32_t instanceIndex, std::string name, int32_t idOffset, LFOConfig* cfg);

				};

			}
		}
	}
}
