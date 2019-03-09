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

			IntegerControl(int32_t id, std::string name, std::weak_ptr<IntegerLaw> law, float precision, int32_t initialValue);

		};

	}
}
