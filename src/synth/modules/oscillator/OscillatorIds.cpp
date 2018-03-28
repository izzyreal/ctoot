// Generated from /toot2/src/uk/org/toot/synth/modules/oscillator/OscillatorIds.java
#include <synth/modules/oscillator/OscillatorIds.hpp>

 ctoot::synth::modules::oscillator::OscillatorIds::OscillatorIds(const ::default_init_tag&)
    : super(*static_cast< ::default_init_tag* >(0))
{
    clinit();
}

 ctoot::synth::modules::oscillator::OscillatorIds::OscillatorIds()
    : OscillatorIds(*static_cast< ::default_init_tag* >(0))
{
    ctor();
}

constexpr int32_t ctoot::synth::modules::oscillator::OscillatorIds::OSCILLATOR_BASE_ID;

constexpr int32_t ctoot::synth::modules::oscillator::OscillatorIds::WAVE_OSCILLATOR_ID;

constexpr int32_t ctoot::synth::modules::oscillator::OscillatorIds::MULTI_WAVE_OSCILLATOR_ID;

constexpr int32_t ctoot::synth::modules::oscillator::OscillatorIds::LFO_ID;

constexpr int32_t ctoot::synth::modules::oscillator::OscillatorIds::ENHANCED_LFO_ID;

constexpr int32_t ctoot::synth::modules::oscillator::OscillatorIds::DUAL_MULTI_WAVE_OSCILLATOR_ID;

constexpr int32_t ctoot::synth::modules::oscillator::OscillatorIds::DSF_OSCILLATOR_ID;

constexpr int32_t ctoot::synth::modules::oscillator::OscillatorIds::HAMMOND_OSCILLATOR_ID;

constexpr int32_t ctoot::synth::modules::oscillator::OscillatorIds::UNISON_ID;

extern java::lang::Class *class_(const char16_t *c, int n);

java::lang::Class* ctoot::synth::modules::oscillator::OscillatorIds::class_()
{
    static ::java::lang::Class* c = ::class_("uk.org.toot.synth.modules.oscillator.OscillatorIds", 50);
    return c;
}

java::lang::Class* ctoot::synth::modules::oscillator::OscillatorIds::getClass0()
{
    return class_();
}

