#pragma once

#include <synth/modules/filter/FilterControls.hpp>
#include <synth/modules/filter/StateVariableFilterVariables.hpp>

namespace ctoot {

    namespace control {
        class LawControl;
        class BooleanControl;
    }

    namespace synth::modules::filter {

        class StateVariableFilterControls
                : public FilterControls, public virtual StateVariableFilterVariables
        {

        private:
            ctoot::control::LawControl *modeMixControl{nullptr};
            ctoot::control::BooleanControl *bandModeControl{nullptr};
            bool bandMode{false};

        public:
            void derive(ctoot::control::Control *c) override;

            void createControls() override;

            void deriveSampleRateIndependentVariables() override;

            float deriveResonance() override;

            virtual ctoot::control::LawControl *createModeMixControl();

            virtual ctoot::control::BooleanControl *createBandModeControl();

        public:

            StateVariableFilterControls(std::string name, int idOffset);

        public:
            float getCutoff() override;

            float getResonance() override;

        };

    }
}
