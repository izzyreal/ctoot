#pragma once

#include <control/FloatControl.hpp>

#include <memory>

namespace ctoot {

	namespace control {
		class ControlLaw;
	}

	namespace audio {
		namespace dynamics {

			class CrossoverControl
				: public ctoot::control::FloatControl
			{

			private:
				static std::weak_ptr<ctoot::control::ControlLaw> XO_LAW();

			protected:
				void ctor(std::string name, float freq);

			public:
				virtual int32_t getFrequency();

			public:
				CrossoverControl(std::string name, float freq);

			};

		}
	}
}
