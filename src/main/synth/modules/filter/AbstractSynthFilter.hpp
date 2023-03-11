#pragma once

namespace ctoot::synth::modules::filter {

    class FilterVariables;

    class AbstractFilter
    {

    public:
        FilterVariables *vars{};
        float fs{44100.0};

    public:
        virtual void setSampleRate(int rate);

        AbstractFilter(FilterVariables *filterVariables);

    };
}
