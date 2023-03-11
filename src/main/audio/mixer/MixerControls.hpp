#pragma once

#include <control/CompoundControl.hpp>
#include <audio/mixer/BusControls.hpp>
#include <audio/core/AudioControlsChain.hpp>
#include <audio/fader/FaderControl.hpp>

#include <memory>
#include <vector>
#include <string>

namespace ctoot::audio::mixer {

    class MixerControls
            : public ctoot::control::CompoundControl
    {

    private:
        bool canAddBusses{true};
        std::shared_ptr<BusControls> mainBusControls{nullptr};
        std::vector<std::shared_ptr<BusControls>> auxBusControls{};
        float smoothingFactor{0.05f};

    public:
        int getProviderId() override;

        virtual float getSmoothingFactor();

        virtual void createAuxBusControls(std::string name, std::weak_ptr<ctoot::audio::core::ChannelFormat> format);

        virtual std::weak_ptr<BusControls> getBusControls(std::string name);

        virtual std::weak_ptr<BusControls> getMainBusControls();

        virtual std::vector<std::shared_ptr<BusControls>> getAuxBusControls();

        virtual std::weak_ptr<ctoot::audio::core::AudioControlsChain>
        createStripControls(int id, int index, std::string name);

        virtual std::weak_ptr<ctoot::audio::core::AudioControlsChain>
        createStripControls(int id, int index, std::string name, bool hasMixControls);

        virtual void addStripControls(std::shared_ptr<CompoundControl> cc);

        virtual std::weak_ptr<ctoot::audio::core::AudioControlsChain> getStripControls(std::string name);

        virtual std::weak_ptr<ctoot::audio::core::AudioControlsChain> getStripControls(int id, int index);

        virtual ctoot::audio::fader::FaderControl *createFaderControl(bool muted);

    public:
        MixerControls(std::string name, std::string mainBusName,
                      std::weak_ptr<ctoot::audio::core::ChannelFormat> channelFormat);

        MixerControls(std::string name)
                : MixerControls(name, "Main", ctoot::audio::core::ChannelFormat::STEREO())
        {}

        MixerControls(std::string name, float _smoothingFactor)
                : MixerControls(name)
        { smoothingFactor = _smoothingFactor; };

    };

}
