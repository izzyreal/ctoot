#pragma once

#include <audio/core/AudioProcess.hpp>

#include <string>

namespace ctoot::audio::system {

    struct AudioPort
            : public virtual ctoot::audio::core::AudioProcess
    {
        virtual std::string getName() = 0;

    };

}
