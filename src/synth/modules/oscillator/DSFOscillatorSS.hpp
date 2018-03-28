// Generated from /toot2/src/uk/org/toot/synth/modules/oscillator/DSFOscillatorSS.java

#pragma once

#include <fwd-toot2.hpp>
#include <dsp/fwd-toot2.hpp>
#include <synth/modules/oscillator/fwd-toot2.hpp>
#include <java/lang/Object.hpp>
#include <synth/modules/oscillator/DSFOscillator.hpp>

struct default_init_tag;

namespace ctoot { namespace synth {modules::oscillator::DSFOscillatorSS
    : public virtual ::java::lang::Object
    , public virtual DSFOscillator
{

public:
    typedef ::java::lang::Object super;

private:
    double a {  };
    int32_t np {  };
    ctoot::dsp::Sine* s1 {  };
    ctoot::dsp::Sine* s2 {  };
    ctoot::dsp::Sine* s3 {  };
    ctoot::dsp::Sine* s4 {  };
    ctoot::dsp::Cosine* cosine {  };
    double aNm1 {  };
protected:
    void ctor(double wn, double wp, int32_t np, float a);

public:
    void update(float a) override;
    float getSample() override;

    // Generated
    DSFOscillatorSS(double wn, double wp, int32_t np, float a);
protected:
    DSFOscillatorSS(const ::default_init_tag&);


public:
    static ::java::lang::Class *class_();

private:
    virtual ::java::lang::Class* getClass0();
};
