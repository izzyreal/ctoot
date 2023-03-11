#pragma once

#include <control/AbstractLaw.hpp>

namespace ctoot {
	namespace control {

		class IntegerLaw
			: public AbstractLaw
		{

		private:
			int32_t res{  };

		public:
			int32_t intValue(float v) override;

            int32_t getResolution() override;

			IntegerLaw(int32_t min, int32_t max, std::string units);

		};

	}
}
