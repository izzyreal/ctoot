// Generated from /toot2/src/uk/org/toot/synth/modules/oscillator/UnisonVariables.java

#pragma once

#include <fwd-toot2.hpp>
#include <synth/modules/oscillator/fwd-toot2.hpp>
#include <java/lang/Object.hpp>

struct ctoot::synth::modules::oscillator::UnisonVariables
    : public virtual ::java::lang::Object
{
    virtual int32_t getOscillatorCount() = 0;
    virtual float getPitchSpread() = 0;
    virtual float getPhaseSpread() = 0;

    // Generated
    static ::java::lang::Class *class_();
};
