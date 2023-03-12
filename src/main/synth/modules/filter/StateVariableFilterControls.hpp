#pragma once

#include <synth/modules/filter/FilterControls.hpp>

namespace ctoot::synth::modules::filter {

    class StateVariableFilterControls
            : public FilterControls
    {
    public:
        void derive(ctoot::control::Control *c) override;

        void deriveSampleRateIndependentVariables() override;

        float deriveResonance() override;

    public:
        StateVariableFilterControls(std::string name, int idOffset);

    public:
        float getCutoff() override;

        float getResonance() override;

    };

}
