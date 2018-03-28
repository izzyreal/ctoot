// Generated from /toot2/src/uk/org/toot/synth/modules/oscillator/OscillatorControl.java

#pragma once

#include <fwd-toot2.hpp>
#include <synth/modules/oscillator/fwd-toot2.hpp>
#include <java/lang/Object.hpp>

struct default_init_tag;

namespace ctoot { namespace synth {modules::oscillator::OscillatorControl
    : public virtual ::java::lang::Object
{

public:
    typedef ::java::lang::Object super;
    bool sync {  };

    // Generated
    OscillatorControl();
protected:
    void ctor();
    OscillatorControl(const ::default_init_tag&);


public:
    static ::java::lang::Class *class_();

private:
    void init();
    virtual ::java::lang::Class* getClass0();
};
