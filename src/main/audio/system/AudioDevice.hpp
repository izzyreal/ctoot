#pragma once

#include <string>
#include <vector>
#include <memory>

namespace ctoot::audio::system {

    struct AudioInput;

    class AudioOutput;

    class AudioDevice
    {
    public:
        virtual std::string getName() = 0;

        virtual void closeAudio() = 0;

    };

}
