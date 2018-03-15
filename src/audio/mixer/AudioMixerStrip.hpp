#pragma once
#include <audio/core/AudioProcessChain.hpp>
#include <audio/mixer/AudioMixer.hpp>

#include <audio/core/MetaInfo.hpp>

#include <memory>

namespace ctoot {
	namespace audio {
		namespace mixer {

			class AudioMixerStrip
				: public core::AudioProcessChain
			{

			public:
				AudioMixer* mixer{ nullptr };

			private:
                ctoot::audio::core::AudioBuffer* buffer{ nullptr };
				std::shared_ptr<ctoot::audio::core::MetaInfo> metaInfo;
				std::weak_ptr<AudioProcess> input;
				std::weak_ptr<AudioProcess> directOutput;
				bool isChannel{ false };
                std::weak_ptr<ctoot::audio::core::ChannelFormat> channelFormat;
				int nmixed{ 1 };

			public:
				virtual std::weak_ptr<AudioProcess> getInputProcess();
				virtual void setInputProcess(std::weak_ptr<AudioProcess> input);
				virtual std::weak_ptr<AudioProcess> getDirectOutputProcess();
				virtual void setDirectOutputProcess(std::weak_ptr<AudioProcess> output);
				virtual void silence();

			public:
				virtual ctoot::audio::core::AudioBuffer* createBuffer();

			private:
				static const int silenceCount{ 1000 };
				int silenceCountdown{};

			public:
				virtual bool processBuffer();
				virtual void checkMetaInfo(std::weak_ptr<ctoot::audio::core::MetaInfo> info);
				virtual int mix(ctoot::audio::core::AudioBuffer* bufferToMix, std::vector<float> gain);

			public:
				std::shared_ptr<AudioProcess> createProcess(std::weak_ptr<ctoot::audio::core::AudioControls> controls) override;
				void close() override;

			public:
				AudioMixerStrip(AudioMixer* mixer, std::weak_ptr<ctoot::audio::core::AudioControlsChain> controlsChain);
				~AudioMixerStrip();

			};

		}
	}
}
