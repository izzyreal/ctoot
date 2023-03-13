#pragma once

#include <control/CompoundControl.hpp>
#include <control/BooleanControl.hpp>

namespace ctoot::audio::core {

    class AudioControls
            : public control::CompoundControl
    {

    public:
        AudioControls(int id, std::string name, int bypassId);

        AudioControls(int id, std::string name);

    };
}
