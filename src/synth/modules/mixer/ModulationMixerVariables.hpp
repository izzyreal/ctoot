// Generated from /toot2/src/uk/org/toot/synth/modules/mixer/ModulationMixerVariables.java

#pragma once

#include <fwd-toot2.hpp>
#include <synth/modules/mixer/fwd-toot2.hpp>
#include <java/lang/Object.hpp>

struct ctoot::synth::modules::mixer::ModulationMixerVariables
    : public virtual ::java::lang::Object
{
    virtual int32_t getCount() = 0;
    virtual float getDepth(int32_t n) = 0;
    virtual ::floatArray* getDepths() = 0;

    // Generated
    static ::java::lang::Class *class_();
};
