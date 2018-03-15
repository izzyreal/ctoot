#pragma once
#include <observer/Observable.hpp>

#include <vector>
#include <memory>

namespace ctoot {
	namespace audio {
		namespace system {
			class AudioDevice;
			class AudioInput;
			class AudioOutput;
			class AudioSystem
				: public moduru::observer::Observable
			{
			public:
				virtual void addAudioDevice(std::weak_ptr<AudioDevice> device) = 0;
				virtual void removeAudioDevice(std::weak_ptr<AudioDevice> device) = 0;
				virtual std::vector<std::weak_ptr<AudioDevice>> getAudioDevices() = 0;
				virtual std::vector<std::weak_ptr<AudioInput>> getAudioInputs() = 0;
				virtual std::vector<std::weak_ptr<AudioOutput>> getAudioOutputs() = 0;
				virtual void setAutoConnect(bool autoConnect) = 0;
				virtual void close() = 0;

			};

		}
	}
}
