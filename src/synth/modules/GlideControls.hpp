#pragma once

#include <control/CompoundControl.hpp>
#include <synth/modules/GlideVariables.hpp>

#include <memory>

namespace ctoot {

	namespace control {
		class ControlLaw;
	}

	namespace synth {
		namespace modules {

			class GlideControls
				: public ctoot::control::CompoundControl
				, public virtual GlideVariables
			{

			public:
				static constexpr int32_t ENABLE{ 0 };
				static constexpr int32_t TIME{ 1 };

			private:
				std::weak_ptr<ctoot::control::FloatControl> timeControl{  };
				std::weak_ptr<ctoot::control::BooleanControl> enableControl{  };
				int32_t glideMillis{  };
				bool glideEnable{  };
				int32_t idOffset{ 0 };

			protected:
				void derive(ctoot::control::Control* c) override;
				virtual void createControls();
				virtual void deriveSampleRateIndependentVariables();
				virtual bool deriveEnable();
				virtual int32_t deriveTime();
				virtual std::shared_ptr<ctoot::control::BooleanControl> createEnableControl();
				virtual std::shared_ptr<ctoot::control::FloatControl> createTimeControl();

			public:
				int32_t getGlideMilliseconds() override;
				bool isGlideEnabled() override;

				GlideControls(int32_t idOffset);
				GlideControls(int32_t id, std::string name, int32_t idOffset);

			private:
				static std::weak_ptr<ctoot::control::ControlLaw> TIME_LAW();

			};

		}
	}
}
