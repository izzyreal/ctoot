#pragma once
#include <audio/system/DefaultAudioSystem.hpp>
#include <audio/mixer/AudioMixer.hpp>

#include <thirdp/any.hpp>

#include <memory>

namespace ctoot {
	namespace audio {
		namespace system {

			class AudioConnection;

			class MixerConnectedAudioSystem
				: public DefaultAudioSystem
			{

			private:
				std::vector<AudioConnection*> connections;
				std::weak_ptr<ctoot::audio::mixer::AudioMixer> mixer;
				std::weak_ptr<ctoot::audio::mixer::MixerControls> mixerControls;

				/*
				* Implement specialized moduru::observable::Observer notify method
				*/
			public:
				void notifyObservers(nonstd::any arg) override;

			public:
				std::vector<AudioConnection*>* getConnections();

            public:
				virtual void createConnection(std::weak_ptr<AudioOutput> from, ctoot::audio::mixer::AudioMixerStrip* to, int flags);
				virtual AudioConnection* getConnectionFrom(std::string from, std::string fromLocation);
				virtual void createConnectionFrom(std::weak_ptr<AudioOutput> output);
				virtual void closeConnectionFrom(std::weak_ptr<AudioOutput> output);
				virtual void closeConnection(AudioConnection* connection);
				virtual std::weak_ptr<AudioOutput> getOutputPort(std::string name, std::string location);
				virtual std::string nameAndLocation(std::weak_ptr<AudioOutput> output);

			public:
				MixerConnectedAudioSystem(std::shared_ptr<ctoot::audio::mixer::AudioMixer> mixer);
				~MixerConnectedAudioSystem();

			};

		}
	}
}
