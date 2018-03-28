// Generated from /toot2/src/uk/org/toot/synth/modules/oscillator/DSFOscillatorVariables.java

#pragma once

#include <fwd-toot2.hpp>
#include <synth/modules/oscillator/fwd-toot2.hpp>
#include <java/lang/Object.hpp>

struct ctoot::synth::modules::oscillator::DSFOscillatorVariables
    : public virtual ::java::lang::Object
{
    virtual int32_t getRatioNumerator() = 0;
    virtual int32_t getRatioDenominator() = 0;
    virtual int32_t getPartialCount() = 0;
    virtual float getPartialRolloffFactor() = 0;
    virtual int32_t getPartialRolloffInt() = 0;
    virtual bool canUseWolfram() = 0;

    // Generated
    static ::java::lang::Class *class_();
};
