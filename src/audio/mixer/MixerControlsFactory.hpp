#pragma once
#include <audio/mixer/MixerControls.hpp>

namespace ctoot {
	namespace audio {
		namespace mixer {

			class MixerControlsFactory
			{

			public:
				static void createBusses(std::weak_ptr<MixerControls> mixerControls, int nsends, int naux);
				static void createBusStrips(std::weak_ptr<MixerControls> mixerControls);
				static void createBusStrips(std::weak_ptr<MixerControls> mixerControls, std::string mainStripName, std::weak_ptr<ctoot::audio::core::ChannelFormat> mainFormat, int nreturns);
				static void createGroupStrips(std::weak_ptr<MixerControls> mixerControls, int ngroups);
				static void createChannelStrips(std::weak_ptr<MixerControls> mixerControls, int nchannels);

			public:
				static void addMixControls(MixerControls* mixerControls, std::weak_ptr<ctoot::audio::core::AudioControlsChain> controls, bool hasMixControls);

			public:
				MixerControlsFactory();

			};

		}
	}
}
