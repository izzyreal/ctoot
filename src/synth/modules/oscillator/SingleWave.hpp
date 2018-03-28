// Generated from /toot2/src/uk/org/toot/synth/modules/oscillator/SingleWave.java

#pragma once

#include <fwd-toot2.hpp>
#include <synth/modules/oscillator/fwd-toot2.hpp>
#include <java/lang/Object.hpp>
#include <synth/modules/oscillator/Wave.hpp>

struct default_init_tag;

namespace ctoot { namespace synth {modules::oscillator::SingleWave
    : public virtual ::java::lang::Object
    , public virtual Wave
{

public:
    typedef ::java::lang::Object super;

private:
    ::floatArray* data {  };
    float period {  };
protected:
    void ctor(::floatArray* data, float period);

public:
    ::floatArray* getData() override;
    float getPeriod() override;
    float get(float index) override;

    // Generated
    SingleWave(::floatArray* data, float period);
protected:
    SingleWave(const ::default_init_tag&);


public:
    static ::java::lang::Class *class_();

private:
    virtual ::java::lang::Class* getClass0();
};
