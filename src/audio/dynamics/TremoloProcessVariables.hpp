// Generated from /toot2/src/uk/org/toot/audio/dynamics/TremoloProcess.java

#pragma once

#include <fwd-toot2.hpp>
#include <audio/dynamics/fwd-toot2.hpp>
#include <java/lang/Object.hpp>

struct uk::org::toot::audio::dynamics::TremoloProcess_Variables
    : public virtual ::java::lang::Object
{
    virtual bool isBypassed() = 0;
    virtual float getDepth() = 0;
    virtual float getRate() = 0;

    // Generated
    static ::java::lang::Class *class_();
};
