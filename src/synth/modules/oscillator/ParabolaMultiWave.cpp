// Generated from /toot2/src/uk/org/toot/synth/modules/oscillator/ParabolaMultiWave.java
#include <synth/modules/oscillator/ParabolaMultiWave.hpp>

#include <java/lang/NullPointerException.hpp>
#include <Array.hpp>

template<typename T>
static T* npc(T* t)
{
    if(!t) throw new ::java::lang::NullPointerException();
    return t;
}

 ctoot::synth::modules::oscillator::ParabolaMultiWave::ParabolaMultiWave(const ::default_init_tag&)
    : super(*static_cast< ::default_init_tag* >(0))
{
    clinit();
}

 ctoot::synth::modules::oscillator::ParabolaMultiWave::ParabolaMultiWave(int32_t size, float fNyquist) 
    : ParabolaMultiWave(*static_cast< ::default_init_tag* >(0))
{
    ctor(size,fNyquist);
}

void modules::oscillator::ParabolaMultiWave::ctor(int32_t size, float fNyquist)
{
    super::ctor(size, fNyquist);
}

float ctoot::synth::modules::oscillator::ParabolaMultiWave::getWidthStartFactor(float width)
{
    return width < 0.5f ? (1.0f - (width / int32_t(2))) : ((1.0f - width) / int32_t(2));
}

float ctoot::synth::modules::oscillator::ParabolaMultiWave::getWidthScalar(float width)
{
    return 1.0f / (int32_t(8) * (width - width * width));
}

int32_t ctoot::synth::modules::oscillator::ParabolaMultiWave::partial(::floatArray* data, int32_t length, int32_t partial, int32_t sign, float comp)
{
    auto amp = comp * int32_t(4) * sign / (partial * partial);
    for (auto i = int32_t(0); i < length; i++) {
        (*data)[i] += amp * (*sinetable)[((i * partial) + (length / int32_t(4))) % length];
    }
    return -sign;
}

void modules::oscillator::ParabolaMultiWave::normalise(::floatArray* data, float max)
{
    max /= 2;
    for (auto i = int32_t(0); i < npc(data)->length; i++) {
        (*data)[i] /= max;
        (*data)[i] -= 1;
    }
}

extern java::lang::Class *class_(const char16_t *c, int n);

java::lang::Class* ctoot::synth::modules::oscillator::ParabolaMultiWave::class_()
{
    static ::java::lang::Class* c = ::class_("uk.org.toot.synth.modules.oscillator.ParabolaMultiWave", 54);
    return c;
}

java::lang::Class* ctoot::synth::modules::oscillator::ParabolaMultiWave::getClass0()
{
    return class_();
}

