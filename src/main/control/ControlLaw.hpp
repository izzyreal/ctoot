#pragma once
#include <cstdint>
#include <string>

namespace ctoot {
	namespace control {

		class ControlLaw
		{

		public:
			virtual int intValue(float userVal);

            virtual int getResolution();
			virtual float getMinimum();
			virtual float getMaximum();
			virtual std::string getUnits();

		};
	}
}
