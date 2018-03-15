#pragma once
#include <audio/system/AudioSystem.hpp>

#include <memory>

namespace ctoot {
	namespace audio {
		namespace system {

			class DefaultAudioSystem
				: public AudioSystem
			{

			protected:
				std::vector<std::weak_ptr<AudioDevice>> devices{};
				moduru::observer::Observer* observer{ nullptr };

			public:
				bool autoConnect{ false };

			public:
				void addAudioDevice(std::weak_ptr<AudioDevice> device) override;

			public:
				virtual void checkUniqueDeviceName(std::weak_ptr<AudioDevice> device);

			public:
				void removeAudioDevice(std::weak_ptr<AudioDevice> device) override;
				std::vector<std::weak_ptr<AudioDevice>> getAudioDevices() override;
				std::vector<std::weak_ptr<AudioInput>> getAudioInputs() override;
				std::vector<std::weak_ptr<AudioOutput>> getAudioOutputs() override;
				void setAutoConnect(bool autoConnect) override;
				void close() override;

			public:
				DefaultAudioSystem();
				virtual ~DefaultAudioSystem();

			};

		}
	}
}
