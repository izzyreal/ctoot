#pragma once

#include "FilterVariables.hpp"

namespace ctoot::synth::modules::filter {

    class StateVariableFilterElement;

    class StateVariableFilter
    {
    public:
        StateVariableFilter(FilterVariables *variables);

        virtual ~StateVariableFilter();

    private:
        StateVariableFilterElement *element{nullptr};
        float res{0.f};
        FilterVariables *vars{};
        float fs{44100.0};

        void setSampleRate(int rate);

    public:
        virtual float update();

        virtual float filter(float sample, float f);

    };
}
