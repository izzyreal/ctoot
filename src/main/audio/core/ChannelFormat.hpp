#pragma once

#include <audio/core/AudioBuffer.hpp>

#include <string>
#include <cstdint>
#include <vector>
#include <memory>

namespace ctoot::audio::core {

    class ChannelFormat
    {

    public:
        virtual int getCount() = 0;

        virtual std::vector<int8_t> getLeft() = 0;

        virtual std::vector<int8_t> getRight() = 0;

        virtual std::string getName() = 0;

        virtual std::string getName(int chan) = 0;

    public:
        int mix(ctoot::audio::core::AudioBuffer *destBuffer, ctoot::audio::core::AudioBuffer *sourceBuffer,
                std::vector<float> &gain);

        static std::weak_ptr<ChannelFormat> STEREO();

    };

}
