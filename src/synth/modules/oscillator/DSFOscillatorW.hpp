// Generated from /toot2/src/uk/org/toot/synth/modules/oscillator/DSFOscillatorW.java

#pragma once

#include <fwd-toot2.hpp>
#include <dsp/fwd-toot2.hpp>
#include <synth/modules/oscillator/fwd-toot2.hpp>
#include <java/lang/Object.hpp>
#include <synth/modules/oscillator/DSFOscillator.hpp>

struct default_init_tag;

namespace ctoot { namespace synth {modules::oscillator::DSFOscillatorW
    : public virtual ::java::lang::Object
    , public virtual DSFOscillator
{

public:
    typedef ::java::lang::Object super;

private:
    double a {  };
    ctoot::dsp::Sine* sine1 {  };
    ctoot::dsp::Sine* sine2 {  };
    ctoot::dsp::Sine* sine3 {  };
    ctoot::dsp::Cosine* cosine {  };
    double aN {  };
    int32_t np {  };
protected:
    void ctor(double wn, double wp, int32_t np, float a);

public:
    void update(float a) override;
    float getSample() override;

    // Generated
    DSFOscillatorW(double wn, double wp, int32_t np, float a);
protected:
    DSFOscillatorW(const ::default_init_tag&);


public:
    static ::java::lang::Class *class_();

private:
    virtual ::java::lang::Class* getClass0();
};
