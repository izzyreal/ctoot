#pragma once
#include <audio/system/MixerConnectedAudioSystem.hpp>
#include <audio/system/AudioConnection.hpp>
#include <audio/system/AudioOutput.hpp>

#include <audio/mixer/AudioMixerStrip.hpp>

#include <memory>

namespace ctoot {
	namespace audio {
		namespace system {

			class MixerInputConnection
				: public AudioConnection
			{

			public:
				typedef AudioConnection super;

			private:
				std::weak_ptr<AudioOutput> from;
				ctoot::audio::mixer::AudioMixerStrip* to{ nullptr };

			public:
				void close() override;
				std::string getOutputName() override;
				std::string getOutputLocation() override;

                MixerInputConnection(MixerConnectedAudioSystem* mca, std::weak_ptr<AudioOutput> from, ctoot::audio::mixer::AudioMixerStrip* to, int flags);;
				~MixerInputConnection();

            };

		}
	}
}
