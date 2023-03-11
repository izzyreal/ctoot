#pragma once

//#include <observer/Observable.hpp>

#include <vector>
#include <memory>

namespace ctoot::audio::system {
    class AudioDevice;

    struct AudioInput;

    class AudioOutput;

    class AudioSystem
    {
    public:
        virtual void addAudioDevice(std::weak_ptr<AudioDevice> device) = 0;

        virtual void removeAudioDevice(std::weak_ptr<AudioDevice> device) = 0;

        virtual void close() = 0;

    };

}
