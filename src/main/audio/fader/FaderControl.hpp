#pragma once
#include <control/LawControl.hpp>
#include <control/ControlLaw.hpp>

#include <cstdint>
#include <memory>

namespace ctoot {
	namespace audio {
		namespace fader {
			
			class FaderLaw;

			class FaderControl
				: public ctoot::control::LawControl
			{

			protected:
				float gain{ 0 };

			public:
				float getGain();

			public:
				static std::weak_ptr<FaderLaw> SEMI_LOG();
				static std::weak_ptr<FaderLaw> LOG();
				static std::weak_ptr<FaderLaw> BROADCAST();
				static float ATTENUATION_CUTOFF();
				static std::weak_ptr<FaderLaw> defaultLaw();

			public:
				FaderControl(int id, std::weak_ptr<ctoot::control::ControlLaw> law, float initialValue);
				virtual ~FaderControl();

			};
		}
	}
}
