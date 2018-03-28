// Generated from /toot2/src/uk/org/toot/synth/modules/oscillator/OscillatorControl.java
#include <synth/modules/oscillator/OscillatorControl.hpp>

 ctoot::synth::modules::oscillator::OscillatorControl::OscillatorControl(const ::default_init_tag&)
    : super(*static_cast< ::default_init_tag* >(0))
{
    clinit();
}

 ctoot::synth::modules::oscillator::OscillatorControl::OscillatorControl()
    : OscillatorControl(*static_cast< ::default_init_tag* >(0))
{
    ctor();
}

void modules::oscillator::OscillatorControl::ctor()
{
    super::ctor();
    init();
}

void modules::oscillator::OscillatorControl::init()
{
    sync = false;
}

extern java::lang::Class *class_(const char16_t *c, int n);

java::lang::Class* ctoot::synth::modules::oscillator::OscillatorControl::class_()
{
    static ::java::lang::Class* c = ::class_("uk.org.toot.synth.modules.oscillator.OscillatorControl", 54);
    return c;
}

java::lang::Class* ctoot::synth::modules::oscillator::OscillatorControl::getClass0()
{
    return class_();
}

