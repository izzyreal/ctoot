#pragma once

namespace ctoot::synth::modules::filter {

    class FilterVariables
    {
    public:
        virtual float getCutoff() = 0;

        virtual float getResonance() = 0;
    };

}
