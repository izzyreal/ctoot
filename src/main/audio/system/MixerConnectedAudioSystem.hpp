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
        std::weak_ptr<ctoot::audio::mixer::AudioMixer> mixer;
        std::weak_ptr<ctoot::audio::mixer::MixerControls> mixerControls;

    public:
        MixerConnectedAudioSystem(std::shared_ptr<ctoot::audio::mixer::AudioMixer> mixer);

    };

}
