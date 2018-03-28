// Generated from /toot2/src/uk/org/toot/synth/modules/filter/LP1pHP1pVariables.java

#pragma once

#include <fwd-toot2.hpp>
#include <synth/modules/filter/fwd-toot2.hpp>
#include <java/lang/Object.hpp>

struct ctoot::synth::modules::filter::LP1pHP1pVariables
    : public virtual ::java::lang::Object
{
    virtual float getHighPassRatio() = 0;
    virtual float getLowPassRatio() = 0;

    // Generated
    static ::java::lang::Class *class_();
};
