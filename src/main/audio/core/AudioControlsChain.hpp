#pragma once

#include <control/CompoundControlChain.hpp>
#include <audio/core/ChannelFormat.hpp>

#include <vector>

namespace ctoot::audio::core {

    class AudioControlsChain : public ctoot::control::CompoundControlChain
    {

    private:
        std::string sourceLabel{""};
        std::string sourceLocation{""};
        std::weak_ptr<ChannelFormat> constraintChannelFormat;

    public:
        std::shared_ptr<ctoot::control::CompoundControl> createControl(std::string name) override;

        int getMaxInstance() override;

    public:
        AudioControlsChain(int id, std::string name);

        AudioControlsChain(int id, int index, std::string name);

    };
}
