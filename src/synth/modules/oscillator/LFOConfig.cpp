#include <synth/modules/oscillator/LFOConfig.hpp>

using namespace ctoot::synth::modules::oscillator;

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

