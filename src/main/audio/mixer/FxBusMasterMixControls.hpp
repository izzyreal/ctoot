#pragma once
#include <audio/mixer/MixControls.hpp>

namespace ctoot {
	namespace audio {
		namespace mixer {

			class FxBusMasterMixControls
				: public MixControls
			{

			public:
				bool canBeInsertedBefore() override;

            public:
				FxBusMasterMixControls(bool hasMixControls, MixerControls* mixerControls, int stripId, std::weak_ptr<BusControls> busControls, bool isMaster);
				bool hasMixControls;

			};

		}
	}
}
