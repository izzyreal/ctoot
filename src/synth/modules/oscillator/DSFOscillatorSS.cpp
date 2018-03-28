// Generated from /toot2/src/uk/org/toot/synth/modules/oscillator/DSFOscillatorSS.java
#include <synth/modules/oscillator/DSFOscillatorSS.hpp>

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

 ctoot::synth::modules::oscillator::DSFOscillatorSS::DSFOscillatorSS(const ::default_init_tag&)
    : super(*static_cast< ::default_init_tag* >(0))
{
    clinit();
}

 ctoot::synth::modules::oscillator::DSFOscillatorSS::DSFOscillatorSS(double wn, double wp, int32_t np, float a) 
    : DSFOscillatorSS(*static_cast< ::default_init_tag* >(0))
{
    ctor(wn,wp,np,a);
}

void modules::oscillator::DSFOscillatorSS::ctor(double wn, double wp, int32_t np, float a)
{
    super::ctor();
    /* assert((wn > 0.0f && wn < ::java::lang::Math::PI) : ::java::lang::StringBuilder().append("wn=")->append(wn)->toString()) */ ;
    /* assert(wp > 0.0f : ::java::lang::StringBuilder().append("wp=")->append(wp)->toString()) */ ;
    /* assert(np > 0 : ::java::lang::StringBuilder().append("np=")->append(np)->toString()) */ ;
    /* assert((a >= 0 && a < 1.0f) : ::java::lang::StringBuilder().append("a=")->append(a)->toString()) */ ;
    if(wn + wp * np >= ::java::lang::Math::PI)
        np = static_cast< int32_t >(((::java::lang::Math::PI - wn) / wp));

    this->np = np;
    s1 = new ctoot::dsp::Sine(wn + wp * (np - int32_t(1)));
    s2 = new ctoot::dsp::Sine(wn + wp * np);
    s3 = new ctoot::dsp::Sine(wn - wp);
    s4 = new ctoot::dsp::Sine(wn);
    cosine = new ctoot::dsp::Cosine(wp);
    update(a);
}

void modules::oscillator::DSFOscillatorSS::update(float a)
{
    this->a = a;
    aNm1 = ::java::lang::Math::pow(a, np - int32_t(1));
}

float ctoot::synth::modules::oscillator::DSFOscillatorSS::getSample()
{
    auto denom = (int32_t(1) - int32_t(2) * a * npc(cosine)->out() + a * a);
    if(denom == 0)
        return 0.0f;

    return static_cast< float >(((npc(s4)->out() - a * (npc(s3)->out() + aNm1 * (npc(s2)->out() - a * npc(s1)->out()))) / denom));
}

extern java::lang::Class *class_(const char16_t *c, int n);

java::lang::Class* ctoot::synth::modules::oscillator::DSFOscillatorSS::class_()
{
    static ::java::lang::Class* c = ::class_("uk.org.toot.synth.modules.oscillator.DSFOscillatorSS", 52);
    return c;
}

java::lang::Class* ctoot::synth::modules::oscillator::DSFOscillatorSS::getClass0()
{
    return class_();
}

