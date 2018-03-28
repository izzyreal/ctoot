#pragma once

#include <control/CompoundControl.hpp>
#include <synth/modules/mixer/ModulationMixerVariables.hpp>

#include <vector>
#include <string>

namespace ctoot {
	namespace synth {
		namespace modules {
			namespace mixer {

				class ModulationMixerControls
					: public ctoot::control::CompoundControl
					, public virtual ModulationMixerVariables
				{

				public:
					static constexpr int32_t DEPTH{ 0 };

				private:
					std::shared_ptr<ctoot::control::ControlLaw> law{  };
					std::vector<std::weak_ptr<ctoot::control::FloatControl>> depthControl{  };
					std::vector<float> depth{  };
					int32_t idOffset{ 0 };
					int32_t count{  };

				protected:
					void derive(ctoot::control::Control* c) override;
					virtual void createControls(std::vector<std::string> labels);
					virtual void deriveSampleRateIndependentVariables();
					virtual float deriveDepth(int32_t i);
					virtual std::shared_ptr<ctoot::control::FloatControl> createDepthControl(int32_t i, std::string label);

				public:
					int32_t getCount() override;
					float getDepth(int32_t n) override;
					std::vector<float> getDepths() override;

					ModulationMixerControls(int32_t instanceIndex, std::string name, int32_t idOffset, std::vector<std::string> labels, bool bipolar);
					ModulationMixerControls(int32_t instanceIndex, std::string name, int32_t idOffset, std::vector<std::string> labels, bool bipolar, float range, std::string units);
				};

			}
		}
	}
}
