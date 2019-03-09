#pragma once

#include <control/BooleanControl.hpp>
#include <string>

namespace ctoot {
	namespace control {

		class BypassControl
			: public BooleanControl
		{

		public:
			BypassControl(int id);
		};
	}
}
