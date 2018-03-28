// Generated from /toot2/src/uk/org/toot/synth/modules/filter/MoogFilterElement.java
#include <synth/modules/filter/MoogFilterElement.hpp>

 ctoot::synth::modules::filter::MoogFilterElement::MoogFilterElement(const ::default_init_tag&)
    : super(*static_cast< ::default_init_tag* >(0))
{
    clinit();
}

 ctoot::synth::modules::filter::MoogFilterElement::MoogFilterElement()
    : MoogFilterElement(*static_cast< ::default_init_tag* >(0))
{
    ctor();
}

float ctoot::synth::modules::filter::MoogFilterElement::filter(float input, float fc, float res)
{
    auto f = fc * 1.16;
    auto fb = res * (1.0 - 0.15 * f * f);
    input -= out4 * fb;
    input *= 0.35013 * (f * f) * (f * f);
    out1 = input + 0.3 * in1 + (int32_t(1) - f) * out1;
    in1 = input;
    out2 = out1 + 0.3 * in2 + (int32_t(1) - f) * out2;
    in2 = out1;
    out3 = out2 + 0.3 * in3 + (int32_t(1) - f) * out3;
    in3 = out2;
    out4 = out3 + 0.3 * in4 + (int32_t(1) - f) * out4;
    in4 = out3;
    return static_cast< float >(out4);
}

extern java::lang::Class *class_(const char16_t *c, int n);

java::lang::Class* ctoot::synth::modules::filter::MoogFilterElement::class_()
{
    static ::java::lang::Class* c = ::class_("uk.org.toot.synth.modules.filter.MoogFilterElement", 50);
    return c;
}

java::lang::Class* ctoot::synth::modules::filter::MoogFilterElement::getClass0()
{
    return class_();
}

