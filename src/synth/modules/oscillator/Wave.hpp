// Generated from /toot2/src/uk/org/toot/synth/modules/oscillator/Wave.java

#pragma once

#include <fwd-toot2.hpp>
#include <synth/modules/oscillator/fwd-toot2.hpp>
#include <java/lang/Object.hpp>

struct ctoot::synth::modules::oscillator::Wave
    : public virtual ::java::lang::Object
{
    virtual ::floatArray* getData() = 0;
    virtual float getPeriod() = 0;
    virtual float get(float index) = 0;

    // Generated
    static ::java::lang::Class *class_();
};
