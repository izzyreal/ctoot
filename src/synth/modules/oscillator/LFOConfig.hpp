// Generated from /toot2/src/uk/org/toot/synth/modules/oscillator/LFOConfig.java

#pragma once

#include <fwd-toot2.hpp>
#include <synth/modules/oscillator/fwd-toot2.hpp>
#include <java/lang/Object.hpp>

struct default_init_tag;

namespace ctoot { namespace synth {modules::oscillator::LFOConfig
    : public virtual ::java::lang::Object
{

public:
    typedef ::java::lang::Object super;
    float rateMin {  };
    float rateMax {  };
    float rate {  };
    float deviationMax {  };
    float deviation {  };

    // Generated
    LFOConfig();
protected:
    void ctor();
    LFOConfig(const ::default_init_tag&);


public:
    static ::java::lang::Class *class_();

private:
    void init();
    virtual ::java::lang::Class* getClass0();
};
