#pragma once
#include <synth/modules/filter/AbstractSynthFilter.hpp>

namespace ctoot {
	namespace synth {
		namespace modules {
			namespace filter {

				class StateVariableFilterElement;
				class StateVariableFilterVariables;

				class StateVariableFilter
					: AbstractFilter
				{
                public:
                    StateVariableFilter(StateVariableFilterVariables* variables);
                    virtual ~StateVariableFilter();

				private:
					StateVariableFilterElement* element{ nullptr };
					float res{ 0.f };

				public:
					virtual float update();
					virtual float filter(float sample, float f);

				};
			}
		}
	}
}
