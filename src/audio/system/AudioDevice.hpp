#pragma once

//#include <misc/IObservable.hpp>
#include <observer/Observable.hpp>

#include <string>
#include <vector>
#include <memory>

namespace ctoot {
	namespace audio {
		namespace system {

			class AudioInput;
			class AudioOutput;
			class AudioDevice
				: public virtual moduru::observer::Observable
			{
			public:
				virtual std::string getName() = 0;
				virtual std::vector<std::weak_ptr<AudioInput>> getAudioInputs() = 0;
				virtual std::vector<std::weak_ptr<AudioOutput>> getAudioOutputs() = 0;
				virtual void closeAudio() = 0;

			};

		}
	}
}
