// Generated from /toot2/src/uk/org/toot/synth/modules/filter/LP1pFilter.java
#include <synth/modules/filter/LP1pFilter.hpp>

#include <java/lang/Math.hpp>
#include <audio/core/FloatDenormals.hpp>

 ctoot::synth::modules::filter::LP1pFilter::LP1pFilter(const ::default_init_tag&)
    : super(*static_cast< ::default_init_tag* >(0))
{
    clinit();
}

 ctoot::synth::modules::filter::LP1pFilter::LP1pFilter(float freq, int32_t rate) 
    : LP1pFilter(*static_cast< ::default_init_tag* >(0))
{
    ctor(freq,rate);
}

void modules::filter::LP1pFilter::init()
{
    y1 = 0.0f;
}

void modules::filter::LP1pFilter::ctor(float freq, int32_t rate)
{
    super::ctor();
    init();
    g = 1.0f - static_cast< float >(::java::lang::Math::exp(-2.0 * ::java::lang::Math::PI * freq / rate));
}

float ctoot::synth::modules::filter::LP1pFilter::filter(float sample)
{
    y1 = ctoot::audio::core::FloatDenormals::zeroDenorm(y1 + g * (sample - y1));
    return y1;
}

extern java::lang::Class *class_(const char16_t *c, int n);

java::lang::Class* ctoot::synth::modules::filter::LP1pFilter::class_()
{
    static ::java::lang::Class* c = ::class_("uk.org.toot.synth.modules.filter.LP1pFilter", 43);
    return c;
}

java::lang::Class* ctoot::synth::modules::filter::LP1pFilter::getClass0()
{
    return class_();
}

