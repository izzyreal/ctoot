#pragma once

#include <audio/system/DefaultAudioSystem.hpp>
#include <audio/mixer/AudioMixer.hpp>

#include <thirdp/any.hpp>

#include <memory>

namespace ctoot::audio::system {

    class AudioConnection;

    class MixerConnectedAudioSystem : public DefaultAudioSystem
    {

    private:
        std::vector<AudioConnection *> connections;
        std::weak_ptr<ctoot::audio::mixer::AudioMixer> mixer;
        std::weak_ptr<ctoot::audio::mixer::MixerControls> mixerControls;

    public:
        std::vector<AudioConnection *> *getConnections();

    public:
        virtual void
        createConnection(std::weak_ptr<AudioOutput> from, ctoot::audio::mixer::AudioMixerStrip *to, int flags);

        virtual AudioConnection *getConnectionFrom(std::string from, std::string fromLocation);

        virtual void createConnectionFrom(std::weak_ptr<AudioOutput> output);

        virtual void closeConnectionFrom(std::weak_ptr<AudioOutput> output);

        virtual void closeConnection(AudioConnection *connection);

    public:
        MixerConnectedAudioSystem(std::shared_ptr<ctoot::audio::mixer::AudioMixer> mixer);

        ~MixerConnectedAudioSystem();

    };

}
