#pragma once

#include <control/CompoundControl.hpp>
#include <synth/modules/oscillator/LFOVariables.hpp>

namespace ctoot {
	namespace synth {
		namespace modules {
			namespace oscillator {

				class LFOControls
					: public ctoot::control::CompoundControl
					, public virtual LFOVariables
				{

				public:
					typedef ctoot::control::CompoundControl super;
					static constexpr int32_t FREQUENCY{ int32_t(0) };
					static constexpr int32_t DEVIATION{ int32_t(1) };
					static constexpr int32_t SHAPE{ int32_t(2) };

				private:
					ctoot::control::FloatControl* frequencyControl{  };
					ctoot::control::FloatControl* deviationControl{  };
					ctoot::control::EnumControl* shapeControl{  };

				protected:
					int32_t idOffset{  };

				private:
					float frequency{  }, deviation{  };
					bool sine{  };

				protected:
					LFOConfig * config{  };
				protected:
					void ctor(int32_t instanceIndex, std::string name, int32_t idOffset, LFOConfig* cfg);
					void ctor(int32_t id, int32_t instanceIndex, std::string name, int32_t idOffset, LFOConfig* cfg);

				protected:
					void derive(ctoot::control::Control* c) override;
					virtual void createControls();
					virtual ctoot::control::EnumControl* createShapeControl();
					virtual ctoot::control::FloatControl* createFrequencyControl();
					virtual ctoot::control::FloatControl* createDeviationControl();
					virtual void deriveSampleRateIndependentVariables();
					virtual void deriveSampleRateDependentVariables();
					virtual float deriveFrequency();
					virtual float deriveDeviation();
					virtual bool deriveShape();

				public:
					float getFrequency() override;
					float getDeviation() override;
					bool isSine() override;

					// Generated
					LFOControls(int32_t instanceIndex, std::string name, int32_t idOffset, LFOConfig* cfg);
					LFOControls(int32_t id, int32_t instanceIndex, std::string name, int32_t idOffset, LFOConfig* cfg);
				protected:
					LFOControls(const ::default_init_tag&);


				public:
					static ::java::lang::Class *class_();

				private:
					virtual ::java::lang::Class* getClass0();
					friend class LFOControls_createShapeControl_1;
				};

			}
		}
	}
}
