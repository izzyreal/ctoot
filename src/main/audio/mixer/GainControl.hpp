#pragma once
#include <audio/fader/FaderControl.hpp>

namespace ctoot {
	namespace audio {
		namespace mixer {

			class GainControl
				: public audio::fader::FaderControl
			{

			public:
				void setValue(float value) override;

            public:
				GainControl(bool muted);
				virtual ~GainControl();

			};

		}
	}
}
