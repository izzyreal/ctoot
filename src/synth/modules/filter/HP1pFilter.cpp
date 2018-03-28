// Generated from /toot2/src/uk/org/toot/synth/modules/filter/HP1pFilter.java
#include <synth/modules/filter/HP1pFilter.hpp>

 ctoot::synth::modules::filter::HP1pFilter::HP1pFilter(const ::default_init_tag&)
    : super(*static_cast< ::default_init_tag* >(0))
{
    clinit();
}

 ctoot::synth::modules::filter::HP1pFilter::HP1pFilter(float freq, int32_t rate) 
    : HP1pFilter(*static_cast< ::default_init_tag* >(0))
{
    ctor(freq,rate);
}

void modules::filter::HP1pFilter::ctor(float freq, int32_t rate)
{
    super::ctor(freq, rate);
}

float ctoot::synth::modules::filter::HP1pFilter::filter(float sample)
{
    return sample - super::filter(sample);
}

extern java::lang::Class *class_(const char16_t *c, int n);

java::lang::Class* ctoot::synth::modules::filter::HP1pFilter::class_()
{
    static ::java::lang::Class* c = ::class_("uk.org.toot.synth.modules.filter.HP1pFilter", 43);
    return c;
}

java::lang::Class* ctoot::synth::modules::filter::HP1pFilter::getClass0()
{
    return class_();
}

