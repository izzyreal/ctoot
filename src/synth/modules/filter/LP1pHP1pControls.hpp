#pragma once

#include <control/CompoundControl.hpp>
#include <synth/modules/filter/LP1pHP1pVariables.hpp>

#include <memory>

namespace ctoot {
	namespace synth {
		namespace modules {
			namespace filter {
				class LP1pHP1pControls
					: public ctoot::control::CompoundControl
					, public virtual LP1pHP1pVariables
				{

				private:
					static constexpr int32_t LPRATIO{ 0 };
					static constexpr int32_t HPRATIO{ 1 };
					std::weak_ptr<ctoot::control::FloatControl> lpRatioControl{  };
					std::weak_ptr<ctoot::control::FloatControl> hpRatioControl{  };
					float hpRatio{  }, lpRatio{  };

				protected:
					int32_t idOffset{ 0 };

				private:
					int32_t sampleRate{ 44100 };

				protected:
					void derive(ctoot::control::Control* c) override;
					virtual void createControls();
					virtual void deriveSampleRateIndependentVariables();
					virtual void deriveSampleRateDependentVariables();
					virtual float deriveLPRatio();
					virtual float deriveHPRatio();
					virtual std::shared_ptr<ctoot::control::FloatControl> createLPRatioControl();
					virtual std::shared_ptr<ctoot::control::FloatControl> createHPRatioControl();

				public:
					virtual void setSampleRate(int32_t rate);
					float getHighPassRatio() override;
					float getLowPassRatio() override;

					LP1pHP1pControls(int32_t id, int32_t instanceIndex, std::string name, int32_t idOffset);

				private:
					static std::weak_ptr<ctoot::control::ControlLaw> LP_LAW();
					static std::weak_ptr<ctoot::control::ControlLaw> HP_LAW();
				};

			}
		}
	}
}
