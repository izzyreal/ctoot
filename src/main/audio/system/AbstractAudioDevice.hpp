#pragma once
#include <audio/system/AudioDevice.hpp>

namespace ctoot {
	namespace audio {
		namespace system {

			class AbstractAudioDevice
				: public virtual AudioDevice
			{

			public:
				std::vector<std::shared_ptr<AudioInput>> inputs{};
				std::vector<std::shared_ptr<AudioOutput>> outputs{};

			private:
				std::string name{ "" };

			public:
				std::vector<std::weak_ptr<AudioInput>> getAudioInputs() override;
				std::vector<std::weak_ptr<AudioOutput>> getAudioOutputs() override;
				std::string getName() override;
				std::string toString();

			public:
				virtual void addAudioInput(std::shared_ptr<AudioInput> input);
				virtual void removeAudioInput(std::weak_ptr<AudioInput> input);
				virtual void addAudioOutput(std::shared_ptr<AudioOutput> output);
				virtual void removeAudioOutput(std::weak_ptr<AudioOutput> output);

			public:
				AbstractAudioDevice(std::string name);
				~AbstractAudioDevice();

			};

		}
	}
}
