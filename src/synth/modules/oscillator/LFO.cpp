// Generated from /toot2/src/uk/org/toot/synth/modules/oscillator/LFO.java
#include <synth/modules/oscillator/LFO.hpp>

#include <java/lang/Math.hpp>
#include <java/lang/NullPointerException.hpp>
#include <dsp/FastMath.hpp>
#include <synth/modules/oscillator/LFOVariables.hpp>

template<typename T>
static T* npc(T* t)
{
    if(!t) throw new ::java::lang::NullPointerException();
    return t;
}

 ctoot::synth::modules::oscillator::LFO::LFO(const ::default_init_tag&)
    : super(*static_cast< ::default_init_tag* >(0))
{
    clinit();
}

 ctoot::synth::modules::oscillator::LFO::LFO(LFOVariables* vars, float initPhase) 
    : LFO(*static_cast< ::default_init_tag* >(0))
{
    ctor(vars,initPhase);
}

 ctoot::synth::modules::oscillator::LFO::LFO(LFOVariables* vars) 
    : LFO(*static_cast< ::default_init_tag* >(0))
{
    ctor(vars);
}

void modules::oscillator::LFO::init()
{
    shape = int32_t(0);
    modulatorPhase = 0.0f;
}

void modules::oscillator::LFO::ctor(LFOVariables* vars, float initPhase)
{
    ctor(vars);
    modulatorPhase = initPhase;
}

void modules::oscillator::LFO::ctor(LFOVariables* vars)
{
    super::ctor();
    init();
    this->vars = vars;
    auto spread = vars->getDeviation();
    rateDelta = spread * static_cast< float >(::java::lang::Math::random()) - spread / int32_t(2);
    setSampleRate(44100);
}

void modules::oscillator::LFO::setSampleRate(int32_t sampleRate)
{
    xDelta = static_cast< float >((int32_t(2) * ::java::lang::Math::PI / sampleRate));
}

void modules::oscillator::LFO::update()
{
    phaseDelta = xDelta * (vars->getFrequency() + rateDelta);
    shape = vars->isSine() ? int32_t(0) : int32_t(1);
}

float ctoot::synth::modules::oscillator::LFO::getSample()
{
    modulatorPhase += phaseDelta;
    if(modulatorPhase > ::java::lang::Math::PI) {
        modulatorPhase -= int32_t(2) * ::java::lang::Math::PI;
    }
    return (shape == 0) ? ctoot::dsp::FastMath::sin(modulatorPhase) : ctoot::dsp::FastMath::triangle(modulatorPhase);
}

extern java::lang::Class *class_(const char16_t *c, int n);

java::lang::Class* ctoot::synth::modules::oscillator::LFO::class_()
{
    static ::java::lang::Class* c = ::class_("uk.org.toot.synth.modules.oscillator.LFO", 40);
    return c;
}

java::lang::Class* ctoot::synth::modules::oscillator::LFO::getClass0()
{
    return class_();
}

