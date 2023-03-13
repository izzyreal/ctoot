#pragma once

#include <audio/mixer/MixProcess.hpp>
#include <audio/mixer/MixVariables.hpp>

namespace ctoot::audio::mixer {

    class MainMixProcess
            : public MixProcess
    {
    public:
        std::shared_ptr<AudioMixerStrip> nextRoutedStrip;

    public:
        ctoot::control::EnumControl *routeControl{nullptr};

    public:
        AudioMixerStrip *getRoutedStrip() override;

    public:
        MainMixProcess(std::shared_ptr<AudioMixerStrip> strip, std::shared_ptr<MixVariables> vars, AudioMixer *mixer);

    };

}
