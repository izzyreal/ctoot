#pragma once
#include <control/CompoundControl.hpp>

namespace ctoot {
	namespace control {

		class ControlRow
			: public CompoundControl
		{

		public:
			typedef CompoundControl super;

		public:

            ControlRow();

		private:
			friend class CompoundControl;
			friend class ControlColumn;
			friend class BypassControl;
		};
	}
}
