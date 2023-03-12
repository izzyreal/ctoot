#pragma once

#include <audio/fader/FaderControl.hpp>

#include <memory>

namespace ctoot::mpc {

    class MpcFaderControl
            : public ctoot::audio::fader::FaderControl
    {

    private:
        static std::weak_ptr<ctoot::control::ControlLaw> MPC_FADER_LAW();

    public:
        void setValue(float value) override;

        MpcFaderControl(bool muted);

    };

}
