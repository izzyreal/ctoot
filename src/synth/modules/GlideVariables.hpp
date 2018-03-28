// Generated from /toot2/src/uk/org/toot/synth/modules/GlideVariables.java

#pragma once

#include <fwd-toot2.hpp>
#include <synth/modules/fwd-toot2.hpp>
#include <java/lang/Object.hpp>

struct ctoot::synth::modules::GlideVariables
    : public virtual ::java::lang::Object
{
    virtual bool isGlideEnabled() = 0;
    virtual int32_t getGlideMilliseconds() = 0;

    // Generated
    static ::java::lang::Class *class_();
};
