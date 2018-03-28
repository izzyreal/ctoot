// Generated from /toot2/src/uk/org/toot/synth/modules/oscillator/OscillatorIds.java

#pragma once

#include <fwd-toot2.hpp>
#include <synth/modules/oscillator/fwd-toot2.hpp>
#include <java/lang/Object.hpp>

struct default_init_tag;

namespace ctoot { namespace synth {modules::oscillator::OscillatorIds
    : public virtual ::java::lang::Object
{

public:
    typedef ::java::lang::Object super;

public: /* package */
    static constexpr int32_t OSCILLATOR_BASE_ID { int32_t(0) };
    static constexpr int32_t WAVE_OSCILLATOR_ID { int32_t(1) };
    static constexpr int32_t MULTI_WAVE_OSCILLATOR_ID { int32_t(2) };
    static constexpr int32_t LFO_ID { int32_t(3) };
    static constexpr int32_t ENHANCED_LFO_ID { int32_t(4) };
    static constexpr int32_t DUAL_MULTI_WAVE_OSCILLATOR_ID { int32_t(5) };
    static constexpr int32_t DSF_OSCILLATOR_ID { int32_t(6) };
    static constexpr int32_t HAMMOND_OSCILLATOR_ID { int32_t(7) };
    static constexpr int32_t UNISON_ID { int32_t(31) };

    // Generated

public:
    OscillatorIds();
protected:
    OscillatorIds(const ::default_init_tag&);


public:
    static ::java::lang::Class *class_();

private:
    virtual ::java::lang::Class* getClass0();
};
