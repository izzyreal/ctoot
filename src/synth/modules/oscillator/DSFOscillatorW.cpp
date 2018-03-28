// Generated from /toot2/src/uk/org/toot/synth/modules/oscillator/DSFOscillatorW.java
#include <synth/modules/oscillator/DSFOscillatorW.hpp>

#include <java/lang/Math.hpp>
#include <java/lang/NullPointerException.hpp>
#include <java/lang/String.hpp>
#include <java/lang/StringBuilder.hpp>
#include <dsp/Cosine.hpp>
#include <dsp/Sine.hpp>

template<typename T>
static T* npc(T* t)
{
    if(!t) throw new ::java::lang::NullPointerException();
    return t;
}

 ctoot::synth::modules::oscillator::DSFOscillatorW::DSFOscillatorW(const ::default_init_tag&)
    : super(*static_cast< ::default_init_tag* >(0))
{
    clinit();
}

 ctoot::synth::modules::oscillator::DSFOscillatorW::DSFOscillatorW(double wn, double wp, int32_t np, float a) 
    : DSFOscillatorW(*static_cast< ::default_init_tag* >(0))
{
    ctor(wn,wp,np,a);
}

void modules::oscillator::DSFOscillatorW::ctor(double wn, double wp, int32_t np, float a)
{
    super::ctor();
    /* assert((wn > 0.0f && wn < ::java::lang::Math::PI) : ::java::lang::StringBuilder().append("wn=")->append(wn)->toString()) */ ;
    /* assert(np > 0 : ::java::lang::StringBuilder().append("np=")->append(np)->toString()) */ ;
    /* assert((a >= 0 && a < 1.0f) : ::java::lang::StringBuilder().append("a=")->append(a)->toString()) */ ;
    this->np = np;
    if(wn * np >= ::java::lang::Math::PI)
        np = static_cast< int32_t >((::java::lang::Math::PI / wn));

    sine1 = new ctoot::dsp::Sine(wn * (np + int32_t(1)));
    sine2 = new ctoot::dsp::Sine(wn * np);
    sine3 = new ctoot::dsp::Sine(wn);
    cosine = new ctoot::dsp::Cosine(wn);
    update(a);
}

void modules::oscillator::DSFOscillatorW::update(float a)
{
    this->a = a;
    aN = ::java::lang::Math::pow(a, np);
}

float ctoot::synth::modules::oscillator::DSFOscillatorW::getSample()
{
    auto denom = (int32_t(1) - int32_t(2) * a * npc(cosine)->out() + a * a);
    if(denom == 0)
        return 0.0f;

    return static_cast< float >(((((a * npc(sine2)->out() - npc(sine1)->out()) * aN + npc(sine3)->out()) * a) / denom));
}

extern java::lang::Class *class_(const char16_t *c, int n);

java::lang::Class* ctoot::synth::modules::oscillator::DSFOscillatorW::class_()
{
    static ::java::lang::Class* c = ::class_("uk.org.toot.synth.modules.oscillator.DSFOscillatorW", 51);
    return c;
}

java::lang::Class* ctoot::synth::modules::oscillator::DSFOscillatorW::getClass0()
{
    return class_();
}

