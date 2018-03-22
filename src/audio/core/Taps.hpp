#pragma once

#include <string>
#include <vector>

namespace ctoot {
	namespace audio {

		namespace basic {
			namespace tap {
				class TapControls;
			}
		}

		namespace server {
			class AudioServer;
		}

		namespace core {

			class AudioBuffer;
			class TapControl;

			class Taps
			{


			public:
				static std::vector<ctoot::audio::basic::tap::TapControls*> taps;

			private:
				static ctoot::audio::server::AudioServer* server;

			public:
				static void setAudioServer(ctoot::audio::server::AudioServer* aserver);
				static AudioBuffer* create(ctoot::audio::basic::tap::TapControls* controls);
				static void remove(AudioBuffer* buffer);
				static ctoot::audio::basic::tap::TapControls* getControls(std::string name);
				static AudioBuffer* getBuffer(std::string name);

			private:
				static void check();

			public:
				static std::string tapName(ctoot::audio::basic::tap::TapControls* controls);

			};

		}
	}
}
