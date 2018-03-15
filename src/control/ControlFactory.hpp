#pragma once

#include <memory>

namespace ctoot {
	namespace control {
		class Control;
		class ControlFactory
		{
		public:
			virtual std::shared_ptr<Control> create() = 0;
		};
	}
}
