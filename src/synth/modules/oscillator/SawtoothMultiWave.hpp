// Generated from /toot2/src/uk/org/toot/synth/modules/oscillator/SawtoothMultiWave.java

#pragma once

#include <fwd-toot2.hpp>
#include <synth/modules/oscillator/fwd-toot2.hpp>
#include <synth/modules/oscillator/MultiWave.hpp>

struct default_init_tag;

namespace ctoot { namespace synth {modules::oscillator::SawtoothMultiWave
    : public MultiWave
{

public:
    typedef MultiWave super;
protected:
    void ctor(int32_t size, float fNyquist);

public:
    float getWidthOffset(float width) override;

protected:
    int32_t partial(::floatArray* data, int32_t length, int32_t partial, int32_t sign, float comp) override;

    // Generated

public:
    SawtoothMultiWave(int32_t size, float fNyquist);
protected:
    SawtoothMultiWave(const ::default_init_tag&);


public:
    static ::java::lang::Class *class_();

private:
    virtual ::java::lang::Class* getClass0();
};
