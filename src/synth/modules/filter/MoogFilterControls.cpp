// Generated from /toot2/src/uk/org/toot/synth/modules/filter/MoogFilterControls.java
#include <synth/modules/filter/MoogFilterControls.hpp>

#include <synth/modules/filter/FilterIds.hpp>

 ctoot::synth::modules::filter::MoogFilterControls::MoogFilterControls(const ::default_init_tag&)
    : super(*static_cast< ::default_init_tag* >(0))
{
    clinit();
}

 ctoot::synth::modules::filter::MoogFilterControls::MoogFilterControls(int32_t instanceIndex, std::string name, int32_t idOffset) 
    : MoogFilterControls(*static_cast< ::default_init_tag* >(0))
{
    ctor(instanceIndex,name,idOffset);
}

void modules::filter::MoogFilterControls::ctor(int32_t instanceIndex, std::string name, int32_t idOffset)
{
    super::ctor(FilterIds::MOOG_LPF_ID, instanceIndex, name, idOffset);
}

float ctoot::synth::modules::filter::MoogFilterControls::deriveResonance()
{
    return super::deriveResonance() * int32_t(4);
}

extern java::lang::Class *class_(const char16_t *c, int n);

java::lang::Class* ctoot::synth::modules::filter::MoogFilterControls::class_()
{
    static ::java::lang::Class* c = ::class_("uk.org.toot.synth.modules.filter.MoogFilterControls", 51);
    return c;
}

java::lang::Class* ctoot::synth::modules::filter::MoogFilterControls::getClass0()
{
    return class_();
}

