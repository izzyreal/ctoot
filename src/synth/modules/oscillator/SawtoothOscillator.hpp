// Generated from /toot2/src/uk/org/toot/synth/modules/oscillator/SawtoothOscillator.java

#pragma once

#include <fwd-toot2.hpp>
#include <synth/fwd-toot2.hpp>
#include <synth/modules/oscillator/fwd-toot2.hpp>
#include <java/lang/Object.hpp>

struct default_init_tag;

namespace ctoot { namespace synth {modules::oscillator::SawtoothOscillator
    : public virtual ::java::lang::Object
{

public:
    typedef ::java::lang::Object super;

private:
    static MultiWave* multiWave_;
    ctoot::synth::SynthChannel* channel {  };
    Wave* wave {  };
    int32_t waveSize {  };
    int32_t waveIndex {  };
    float k {  };
    float k2 {  };
    float increment {  };
    float currentIncrement {  };
    float index {  };
    float frequency {  };
protected:
    void ctor(ctoot::synth::SynthChannel* channel, float frequency);

public:
    virtual void setSampleRate(int32_t sampleRate);
    virtual void update();
    virtual float getSample(float mod);

    // Generated
    SawtoothOscillator(ctoot::synth::SynthChannel* channel, float frequency);
protected:
    SawtoothOscillator(const ::default_init_tag&);


public:
    static ::java::lang::Class *class_();
    static void clinit();

private:
    void init();
    static MultiWave*& multiWave();
    virtual ::java::lang::Class* getClass0();
};
