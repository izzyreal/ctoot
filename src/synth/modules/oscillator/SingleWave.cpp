// Generated from /toot2/src/uk/org/toot/synth/modules/oscillator/SingleWave.java
#include <synth/modules/oscillator/SingleWave.hpp>

#include <Array.hpp>

 ctoot::synth::modules::oscillator::SingleWave::SingleWave(const ::default_init_tag&)
    : super(*static_cast< ::default_init_tag* >(0))
{
    clinit();
}

 ctoot::synth::modules::oscillator::SingleWave::SingleWave(::floatArray* data, float period) 
    : SingleWave(*static_cast< ::default_init_tag* >(0))
{
    ctor(data,period);
}

void modules::oscillator::SingleWave::ctor(::floatArray* data, float period)
{
    super::ctor();
    this->data = data;
    this->period = period;
}

floatArray* ctoot::synth::modules::oscillator::SingleWave::getData()
{
    return data;
}

float ctoot::synth::modules::oscillator::SingleWave::getPeriod()
{
    return period;
}

float ctoot::synth::modules::oscillator::SingleWave::get(float index)
{
    auto ix = static_cast< int32_t >(index);
    auto frac = index - ix;
    return (1.0f - frac) * (*data)[ix] + frac * (*data)[ix + int32_t(1)];
}

extern java::lang::Class *class_(const char16_t *c, int n);

java::lang::Class* ctoot::synth::modules::oscillator::SingleWave::class_()
{
    static ::java::lang::Class* c = ::class_("uk.org.toot.synth.modules.oscillator.SingleWave", 47);
    return c;
}

java::lang::Class* ctoot::synth::modules::oscillator::SingleWave::getClass0()
{
    return class_();
}

