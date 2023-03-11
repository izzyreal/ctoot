#pragma once

#include <control/FloatControl.hpp>

namespace ctoot {
	namespace control {

		class IntegerLaw;

		class IntegerControl
			: public FloatControl
		{

		public:
			virtual int32_t getUserValue();
			std::string getValueString() override;

        };

	}
}
