// Generated from /toot2/src/uk/org/toot/synth/modules/oscillator/LFO.java

#pragma once

#include <fwd-toot2.hpp>
#include <synth/modules/oscillator/fwd-toot2.hpp>
#include <java/lang/Object.hpp>

struct default_init_tag;

namespace ctoot { namespace synth {modules::oscillator::LFO
    : public virtual ::java::lang::Object
{

public:
    typedef ::java::lang::Object super;

private:
    int32_t shape {  };
    float modulatorPhase {  };
    float xDelta {  };
    LFOVariables* vars {  };
    float rateDelta {  };
    double phaseDelta {  };
protected:
    void ctor(LFOVariables* vars, float initPhase);
    void ctor(LFOVariables* vars);

public:
    virtual void setSampleRate(int32_t sampleRate);
    virtual void update();
    virtual float getSample();

    // Generated
    LFO(LFOVariables* vars, float initPhase);
    LFO(LFOVariables* vars);
protected:
    LFO(const ::default_init_tag&);


public:
    static ::java::lang::Class *class_();

private:
    void init();
    virtual ::java::lang::Class* getClass0();
};
