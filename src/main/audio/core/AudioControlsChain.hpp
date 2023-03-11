#pragma once

#include <control/CompoundControlChain.hpp>
#include <audio/core/ChannelFormat.hpp>

#include <vector>

namespace ctoot::audio::core {

    class AudioControlsChain : public ctoot::control::CompoundControlChain
    {

    private:
        std::string sourceLabel;
        std::string sourceLocation;
        std::weak_ptr<ChannelFormat> constraintChannelFormat;

    public:
        AudioControlsChain(int id, std::string name);

    };
}
