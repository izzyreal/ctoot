// Generated from /toot2/src/uk/org/toot/synth/modules/mixer/MixerVariables.java

#pragma once

#include <fwd-toot2.hpp>
#include <synth/modules/mixer/fwd-toot2.hpp>
#include <java/lang/Object.hpp>

struct ctoot::synth::modules::mixer::MixerVariables
    : public virtual ::java::lang::Object
{
    virtual int32_t getCount() = 0;
    virtual float getLevel(int32_t n) = 0;

    // Generated
    static ::java::lang::Class *class_();
};
