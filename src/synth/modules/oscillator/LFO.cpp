#include <synth/modules/oscillator/LFO.hpp>

#include <dsp/FastMath.hpp>
#include <synth/modules/oscillator/LFOVariables.hpp>

using namespace ctoot::synth::modules::oscillator;

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
    xDelta = static_cast< float >((int32_t(2) * M_PI / sampleRate));
}

void modules::oscillator::LFO::update()
{
    phaseDelta = xDelta * (vars->getFrequency() + rateDelta);
    shape = vars->isSine() ? int32_t(0) : int32_t(1);
}

float ctoot::synth::modules::oscillator::LFO::getSample()
{
    modulatorPhase += phaseDelta;
    if(modulatorPhase > M_PI) {
        modulatorPhase -= int32_t(2) * M_PI;
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

