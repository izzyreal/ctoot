#pragma once
#include <audio/server/AudioServer.hpp>
#include <audio/server/AudioClient.hpp>
#include <audio/mixer/MixControls.hpp>
#include <audio/mixer/MixerControlsObserver.hpp>

#include <thirdp/concurrentqueue.h>
#include <vector>

namespace ctoot {
	namespace audio {
		namespace mixer {

            class Mutation;
			class AudioMixerStrip;
			class AudioMixerBus;
			class AudioMixer
				: public ctoot::audio::server::AudioClient
			{

			private:
				std::weak_ptr<MixerControls> controls;

			protected:
				std::shared_ptr<AudioMixerBus> mainBus{ nullptr };
				std::vector<std::shared_ptr<AudioMixerBus>> busses{};
				std::vector<std::shared_ptr<AudioMixerBus>> auxBusses{};
				std::vector<std::shared_ptr<AudioMixerBus>> fxBusses{};

			private:
				std::vector<std::shared_ptr<AudioMixerStrip>> strips{};
				std::vector<std::weak_ptr<AudioMixerStrip>> channelStrips{};
				std::vector<std::weak_ptr<AudioMixerStrip>> groupStrips{};
				std::vector<std::weak_ptr<AudioMixerStrip>> fxStrips{};
				std::vector<std::weak_ptr<AudioMixerStrip>> auxStrips{};
				std::weak_ptr<AudioMixerStrip> mainStrip;
				std::weak_ptr<ctoot::audio::server::AudioServer> server{};
                ctoot::audio::core::AudioBuffer* sharedAudioBuffer{ nullptr };
				moodycamel::ConcurrentQueue<Mutation*> mutationQueue{};

				bool enabled{ true };
				std::unique_ptr<MixerControlsObserver> observer;

			public:
				std::weak_ptr<MixerControls> getMixerControls();
				std::weak_ptr<ctoot::audio::server::AudioServer> getAudioServer();
				moodycamel::ConcurrentQueue<Mutation*>& getMutationQueue();

			public:
				ctoot::audio::core::AudioBuffer* getSharedBuffer();
				ctoot::audio::core::AudioBuffer* createBuffer(std::string name);
				void removeBuffer(ctoot::audio::core::AudioBuffer* buffer);

			public:
				bool isMutating();
				void waitForMutations();
				std::weak_ptr<AudioMixerStrip> getStrip(std::string name);
				std::weak_ptr<AudioMixerStrip> getStripImpl(std::string name);
				std::vector<std::shared_ptr<AudioMixerStrip>> getStrips();
				std::weak_ptr<AudioMixerStrip> getUnusedChannelStrip();
				void work(int nFrames) override;

			private:
				void processMutations();
				void evaluateStrips(std::vector<std::weak_ptr<AudioMixerStrip>>* evalStrips);
				void silenceStrips(std::vector<std::weak_ptr<AudioMixerStrip>>* evalStrips);
				void writeBusBuffers();
				void createBusses(std::weak_ptr<MixerControls> mixerControls);
				std::shared_ptr<AudioMixerBus> createBus(std::weak_ptr<BusControls> busControls);

			public:
				void processMutation(Mutation* m);
				std::shared_ptr<AudioMixerBus> getBus(std::string name);
				std::shared_ptr<AudioMixerBus> getMainBus();
				std::weak_ptr<AudioMixerStrip> getMainStrip();

			public:
				void createStrips(std::weak_ptr<MixerControls> mixerControls);
				std::weak_ptr<AudioMixerStrip> createStrip(std::weak_ptr<ctoot::audio::core::AudioControlsChain> controls);
				void removeStrip(std::weak_ptr<ctoot::audio::core::AudioControlsChain> controls);

			public:
				void close();
				bool isEnabled();

			public:
				void setEnabled(bool enabled) override;

			public:
				AudioMixer(std::weak_ptr<MixerControls> controls, std::weak_ptr<ctoot::audio::server::AudioServer> server);
				~AudioMixer();

			};
		}
	}
}
