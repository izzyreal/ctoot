// Generated from /toot2/src/uk/org/toot/synth/modules/oscillator/DSFOscillator.java

#pragma once

#include <fwd-toot2.hpp>
#include <synth/modules/oscillator/fwd-toot2.hpp>
#include <java/lang/Object.hpp>

struct ctoot::synth::modules::oscillator::DSFOscillator
    : public virtual ::java::lang::Object
{
    virtual void update(float a) = 0;
    virtual float getSample() = 0;

    // Generated
    static ::java::lang::Class *class_();
};
