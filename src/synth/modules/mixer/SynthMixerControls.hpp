#pragma once

#include <control/CompoundControl.hpp>
#include <synth/modules/mixer/MixerVariables.hpp>

#include <memory>
#include <cstdint>

namespace ctoot {

	namespace control {
		class FloatControl;
	}

	namespace synth {
		namespace modules {
			namespace mixer {
				class MixerControls
					: public ctoot::control::CompoundControl
					, public virtual MixerVariables
				{

				public:
					static constexpr int32_t LEVEL{ 0 };

				private:
					std::vector<std::weak_ptr<ctoot::control::FloatControl>> levelControl{  };
					std::vector<float> level{  };
					int32_t idOffset{ 0 };
					int32_t count{  };

				protected:
					void derive(ctoot::control::Control* c) override;
					virtual void createControls();
					virtual void deriveSampleRateIndependentVariables();
					virtual float deriveLevel(int32_t i);
					virtual void deriveSampleRateDependentVariables();
					virtual std::shared_ptr<ctoot::control::FloatControl> createLevelControl(int32_t i);

				public:
					int32_t getCount() override;
					float getLevel(int32_t n) override;

					MixerControls(int32_t instanceIndex, std::string name, int32_t idOffset, int32_t count);
					MixerControls(int32_t id, int32_t instanceIndex, std::string name, int32_t idOffset, int32_t count);

				};

			}
		}
	}
}
