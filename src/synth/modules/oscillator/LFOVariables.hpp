// Generated from /toot2/src/uk/org/toot/synth/modules/oscillator/LFOVariables.java

#pragma once

#include <fwd-toot2.hpp>
#include <synth/modules/oscillator/fwd-toot2.hpp>
#include <java/lang/Object.hpp>

struct ctoot::synth::modules::oscillator::LFOVariables
    : public virtual ::java::lang::Object
{
    virtual float getFrequency() = 0;
    virtual float getDeviation() = 0;
    virtual bool isSine() = 0;

    // Generated
    static ::java::lang::Class *class_();
};
