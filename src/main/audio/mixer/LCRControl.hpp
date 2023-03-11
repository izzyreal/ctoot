#pragma once
#include <control/FloatControl.hpp>
#include <vector>
#include <control/ControlLaw.hpp>

namespace ctoot {
	namespace audio {
		namespace mixer {

			class LCRControl
				: public ctoot::control::FloatControl
			{

			public:
				virtual float getLeft() = 0;
				virtual float getRight() = 0;

            public:
				LCRControl(std::string name, std::weak_ptr<ctoot::control::ControlLaw> law, float precision, float initialValue);
				virtual ~LCRControl();

			};

		}
	}
}
