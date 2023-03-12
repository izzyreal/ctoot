#pragma once

#include <synth/ControlChange.hpp>
#include <control/CompoundControl.hpp>

namespace ctoot::synth {

    class SynthChannelControls
            : public ctoot::control::CompoundControl
    {
    public:
        void close() override;

    public:
        SynthChannelControls(int id, std::string name);

    };

}
