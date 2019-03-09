#pragma once

#include <control/CompoundControl.hpp>
#include <synth/modules/amplifier/AmplifierVariables.hpp>

namespace ctoot {

	namespace control {
		class ControlLaw;
		class FloatControl;
	}

	namespace synth {
		namespace modules {
			namespace amplifier {

				class AmplifierControls
					: public ctoot::control::CompoundControl
					, public virtual AmplifierVariables
				{

				private:
					static std::weak_ptr<ctoot::control::ControlLaw> LEVEL_LAW();
					std::weak_ptr<ctoot::control::FloatControl> velocityTrackControl{  };
					std::weak_ptr<ctoot::control::FloatControl> levelControl{  };
					float velocityTrack{  };
					float level{  };
					int32_t idOffset{ 0 };
					bool hasVelocity{  };

				protected:
					void derive(ctoot::control::Control* c) override;
					virtual void createControls();
					virtual void deriveSampleRateIndependentVariables();
					virtual float deriveVelocityTrack();
					virtual float deriveLevel();
					virtual std::shared_ptr<ctoot::control::FloatControl> createVelocityTrackControl();
					virtual std::shared_ptr<ctoot::control::FloatControl> createLevelControl();

				public:
					float getVelocityTrack() override;
					float getLevel() override;

					AmplifierControls(int32_t instanceIndex, std::string name, int32_t idOffset);
					AmplifierControls(int32_t instanceIndex, std::string name, int32_t idOffset, std::string options);
					AmplifierControls(int32_t id, int32_t instanceIndex, std::string name, int32_t idOffset, std::string options);
				};

			}
		}
	}
}
