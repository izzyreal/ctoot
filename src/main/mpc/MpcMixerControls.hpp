#pragma once
#include <audio/mixer/MixerControls.hpp>
#include <mpc/MpcFaderControl.hpp>

#include <string>

namespace ctoot {
	namespace mpc {

		class MpcMixerControls
			: public ctoot::audio::mixer::MixerControls
		{

		public:
			typedef ctoot::audio::mixer::MixerControls super;

		public:
			ctoot::audio::fader::FaderControl* createFaderControl(bool muted) override;

			MpcMixerControls(std::string name, float smoothingFactor);
			~MpcMixerControls();

		};

	}
}
