#pragma once

#include <synth/modules/filter/FilterControls.hpp>
#include <synth/modules/filter/DualStateVariableFilterVariables.hpp>

#include <memory>

namespace ctoot {

	namespace control {
		class EnumControl;
	}

	namespace synth {
		namespace modules {
			namespace filter {

				class DualStateVariableFilterControls
					: public FilterControls
					, public virtual DualStateVariableFilterVariables
				{

				private:
					std::weak_ptr<ctoot::control::EnumControl> typeControl{  };
					DualStateVariableFilterConfig* type{  };

				protected:
					void derive(ctoot::control::Control* c) override;
					void createControls() override;
					void deriveSampleRateIndependentVariables() override;
					float deriveResonance() override;
					virtual DualStateVariableFilterConfig* deriveType();
					virtual std::shared_ptr<ctoot::control::EnumControl> createTypeControl();

				public:
					DualStateVariableFilterConfig * getType() override;

					DualStateVariableFilterControls(int32_t instanceIndex, std::string name, int32_t idOffset);

				public:
					virtual float getCutoff();
					virtual float getResonance();
					virtual void setSampleRate(int32_t rate);

				};

			}
		}
	}
}
