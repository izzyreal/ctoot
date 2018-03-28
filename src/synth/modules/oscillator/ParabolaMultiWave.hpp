// Generated from /toot2/src/uk/org/toot/synth/modules/oscillator/ParabolaMultiWave.java

#pragma once

#include <fwd-toot2.hpp>
#include <synth/modules/oscillator/fwd-toot2.hpp>
#include <synth/modules/oscillator/MultiWave.hpp>

struct default_init_tag;

namespace ctoot { namespace synth {modules::oscillator::ParabolaMultiWave
    : public MultiWave
{

public:
    typedef MultiWave super;
protected:
    void ctor(int32_t size, float fNyquist);

public:
    float getWidthStartFactor(float width) override;
    float getWidthScalar(float width) override;

protected:
    int32_t partial(::floatArray* data, int32_t length, int32_t partial, int32_t sign, float comp) override;
    void normalise(::floatArray* data, float max) override;

    // Generated

public:
    ParabolaMultiWave(int32_t size, float fNyquist);
protected:
    ParabolaMultiWave(const ::default_init_tag&);


public:
    static ::java::lang::Class *class_();

private:
    virtual ::java::lang::Class* getClass0();
};
