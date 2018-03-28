#pragma once

#include <control/EnumControl.hpp>

namespace ctoot {
	namespace synth {
		namespace modules {
			namespace oscillator {

				class ShapeControl
					: public ctoot::control::EnumControl
				{

				public:
					typedef ctoot::control::EnumControl super;
					::java::util::List* getValues() override;

					// Generated
					ShapeControl(LFOControls *LFOControls_this, ::java::util::List* shapeNames, int32_t id, std::string name, ::java::lang::Object* value);
					static ::java::lang::Class *class_();
					LFOControls *LFOControls_this;
					::java::util::List* shapeNames;

				private:
					friend class LFOControls;
				};

			}
		}
	}
}
