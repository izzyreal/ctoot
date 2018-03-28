// Generated from /toot2/src/uk/org/toot/synth/modules/oscillator/SawtoothMultiWave.java
#include <synth/modules/oscillator/SawtoothMultiWave.hpp>

#include <Array.hpp>

 ctoot::synth::modules::oscillator::SawtoothMultiWave::SawtoothMultiWave(const ::default_init_tag&)
    : super(*static_cast< ::default_init_tag* >(0))
{
    clinit();
}

 ctoot::synth::modules::oscillator::SawtoothMultiWave::SawtoothMultiWave(int32_t size, float fNyquist) 
    : SawtoothMultiWave(*static_cast< ::default_init_tag* >(0))
{
    ctor(size,fNyquist);
}

void modules::oscillator::SawtoothMultiWave::ctor(int32_t size, float fNyquist)
{
    super::ctor(size, fNyquist);
}

float ctoot::synth::modules::oscillator::SawtoothMultiWave::getWidthOffset(float width)
{
    return 1.0f - int32_t(2) * width;
}

int32_t ctoot::synth::modules::oscillator::SawtoothMultiWave::partial(::floatArray* data, int32_t length, int32_t partial, int32_t sign, float comp)
{
    auto amp = comp / partial;
    for (auto i = int32_t(0); i < length; i++) {
        (*data)[i] += amp * (*sinetable)[(i * partial) % length];
    }
    return sign;
}

extern java::lang::Class *class_(const char16_t *c, int n);

java::lang::Class* ctoot::synth::modules::oscillator::SawtoothMultiWave::class_()
{
    static ::java::lang::Class* c = ::class_("uk.org.toot.synth.modules.oscillator.SawtoothMultiWave", 54);
    return c;
}

java::lang::Class* ctoot::synth::modules::oscillator::SawtoothMultiWave::getClass0()
{
    return class_();
}

