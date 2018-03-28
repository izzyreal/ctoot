// Generated from /toot2/src/uk/org/toot/synth/modules/filter/MoogFilter2.java
#include <synth/modules/filter/MoogFilter2.hpp>

#include <java/lang/NullPointerException.hpp>
#include <synth/modules/filter/FilterVariables.hpp>
#include <synth/modules/filter/MoogFilterElement.hpp>

template<typename T>
static T* npc(T* t)
{
    if(!t) throw new ::java::lang::NullPointerException();
    return t;
}

 ctoot::synth::modules::filter::MoogFilter2::MoogFilter2(const ::default_init_tag&)
    : super(*static_cast< ::default_init_tag* >(0))
{
    clinit();
}

 ctoot::synth::modules::filter::MoogFilter2::MoogFilter2(FilterVariables* variables) 
    : MoogFilter2(*static_cast< ::default_init_tag* >(0))
{
    ctor(variables);
}

void modules::filter::MoogFilter2::ctor(FilterVariables* variables)
{
    super::ctor(variables);
    element = new MoogFilterElement();
}

float ctoot::synth::modules::filter::MoogFilter2::update()
{
    res = vars->getResonance();
    return vars->getCutoff();
}

float ctoot::synth::modules::filter::MoogFilter2::filter(float sample, float f)
{
    if(f > 1.0f)
        f = 1.0f;

    return element->filter(sample, f, res);
}

extern java::lang::Class *class_(const char16_t *c, int n);

java::lang::Class* ctoot::synth::modules::filter::MoogFilter2::class_()
{
    static ::java::lang::Class* c = ::class_("uk.org.toot.synth.modules.filter.MoogFilter2", 44);
    return c;
}

java::lang::Class* ctoot::synth::modules::filter::MoogFilter2::getClass0()
{
    return class_();
}

