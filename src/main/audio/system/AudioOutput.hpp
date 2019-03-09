#pragma once

#include <audio/system/AudioPort.hpp>

namespace ctoot {
	namespace audio {
		namespace system {

			class AudioOutput
				: public virtual AudioPort
			{
			public:
				virtual std::string getLocation() = 0;

			};

		}
	}
}
