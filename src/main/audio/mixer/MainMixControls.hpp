#pragma once
#include <audio/mixer/MixVariables.hpp>
#include <audio/mixer/MixControls.hpp>
#include <control/EnumControl.hpp>

namespace ctoot {
	namespace audio {
		namespace mixer {

			class MainMixControls
				: public MixControls
			{

			private:
				ctoot::control::EnumControl* routeControl{ nullptr };

			public:
				ctoot::control::EnumControl* createRouteControl(int stripId) override;
				ctoot::control::EnumControl* getRouteControl() override;

			public:
				MainMixControls(MixerControls* mixerControls, int stripId, std::weak_ptr<BusControls> busControls, bool isMaster);
				~MainMixControls();

			};

		}
	}
}
