// Generated from /toot2/src/uk/org/toot/synth/modules/oscillator/OscillatorVariables.java

#pragma once

#include <fwd-toot2.hpp>
#include <synth/modules/oscillator/fwd-toot2.hpp>
#include <java/lang/Object.hpp>

struct ctoot::synth::modules::oscillator::OscillatorVariables
    : public virtual ::java::lang::Object
{
    virtual bool isMaster() = 0;
    virtual float getDetuneFactor() = 0;
    virtual float getSyncThreshold() = 0;

    // Generated
    static ::java::lang::Class *class_();
};
