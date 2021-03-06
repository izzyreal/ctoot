#pragma once
#include <control/ControlLaw.hpp>

namespace ctoot {
	namespace control {

		class AbstractLaw
			: public ControlLaw
		{

		protected:
			static const int resolution{ 16384 };
			float min{};
			float max{};
			std::string units{ "" };

		public:
			int getResolution() override;
			float getMinimum() override;
			float getMaximum() override;
			std::string getUnits() override;

		public:
			AbstractLaw(float min, float max, std::string units);
            virtual ~AbstractLaw() {}
		};

	}
}
