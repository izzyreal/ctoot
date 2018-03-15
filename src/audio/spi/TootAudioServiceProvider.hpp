// Copyright (C) 2006 Steve Taylor.
// Distributed under the Toot Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.toot.org.uk/LICENSE_1_0.txt)

/**
 * The Toot Audio ServiceProvider is implemented so that the
 * provider id and name are only used once.
 */
#pragma once

#include <audio/spi/AudioServiceProvider.hpp>

#include <control/id/ProviderId.hpp>

#include <string>

namespace ctoot {
	namespace audio {
		namespace spi {

			class TootAudioServiceProvider :
				public AudioServiceProvider {

			public:
				TootAudioServiceProvider(std::string description, std::string version)
					: AudioServiceProvider(ctoot::control::id::ProviderId::TOOT_PROVIDER_ID, "Toot Software", description, version) {}

			};

		}
	}
}
