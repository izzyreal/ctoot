// Generated from /toot2/src/uk/org/toot/synth/modules/oscillator/LFOConfig.java
#include <synth/modules/oscillator/LFOConfig.hpp>

 ctoot::synth::modules::oscillator::LFOConfig::LFOConfig(const ::default_init_tag&)
    : super(*static_cast< ::default_init_tag* >(0))
{
    clinit();
}

 ctoot::synth::modules::oscillator::LFOConfig::LFOConfig()
    : LFOConfig(*static_cast< ::default_init_tag* >(0))
{
    ctor();
}

void modules::oscillator::LFOConfig::ctor()
{
    super::ctor();
    init();
}

void modules::oscillator::LFOConfig::init()
{
    rateMin = 0.01f;
    rateMax = 1.0f;
    rate = 0.1f;
    deviationMax = 0.0f;
    deviation = 0.0f;
}

extern java::lang::Class *class_(const char16_t *c, int n);

java::lang::Class* ctoot::synth::modules::oscillator::LFOConfig::class_()
{
    static ::java::lang::Class* c = ::class_("uk.org.toot.synth.modules.oscillator.LFOConfig", 46);
    return c;
}

java::lang::Class* ctoot::synth::modules::oscillator::LFOConfig::getClass0()
{
    return class_();
}

