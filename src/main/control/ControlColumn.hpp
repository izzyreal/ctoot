#pragma once

#include <control/CompoundControl.hpp>

namespace ctoot {
	namespace control {

		class ControlColumn
			: public CompoundControl
		{

		public:
			typedef CompoundControl super;

		public:

            ControlColumn();

		private:
			friend class CompoundControl;
			friend class ControlRow;
			friend class BypassControl;

		};
	}
}
