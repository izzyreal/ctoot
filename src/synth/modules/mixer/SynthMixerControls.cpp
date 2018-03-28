#include <synth/modules/mixer/SynthMixerControls.hpp>

#include <control/Control.hpp>
#include <control/FloatControl.hpp>
#include <control/LawControl.hpp>
#include <control/LinearLaw.hpp>
#include <synth/modules/mixer/MixerIds.hpp>

template<typename ComponentType, typename... Bases> struct SubArray;
namespace java
{
    namespace util
    {
typedef ::SubArray< ::java::util::Observable, ::java::lang::ObjectArray > ObservableArray;
    } // util
} // java

namespace uk
{
    namespace org
    {
        namespace toot
        {
            namespace control
            {
typedef ::SubArray< ctoot::control::Control, ::java::util::ObservableArray > ControlArray;
typedef ::SubArray< ctoot::control::LawControl, ControlArray > LawControlArray;
typedef ::SubArray< ctoot::control::FloatControl, LawControlArray > FloatControlArray;
            } // control
        } // toot
    } // org
} // uk

template<typename T>
static T* npc(T* t)
{
    if(!t) throw new ::java::lang::NullPointerException();
    return t;
}

 ctoot::synth::modules::mixer::MixerControls::MixerControls(const ::default_init_tag&)
    : super(*static_cast< ::default_init_tag* >(0))
{
    clinit();
}

 ctoot::synth::modules::mixer::MixerControls::MixerControls(int32_t instanceIndex, std::string name, int32_t idOffset, int32_t count) 
    : MixerControls(*static_cast< ::default_init_tag* >(0))
{
    ctor(instanceIndex,name,idOffset,count);
}

 ctoot::synth::modules::mixer::MixerControls::MixerControls(int32_t id, int32_t instanceIndex, std::string name, int32_t idOffset, int32_t count) 
    : MixerControls(*static_cast< ::default_init_tag* >(0))
{
    ctor(id,instanceIndex,name,idOffset,count);
}

void modules::mixer::MixerControls::init()
{
    idOffset = int32_t(0);
}

constexpr int32_t ctoot::synth::modules::mixer::MixerControls::LEVEL;

void modules::mixer::MixerControls::ctor(int32_t instanceIndex, std::string name, int32_t idOffset, int32_t count)
{
    ctor(MixerIds::SIMPLE_MIXER_ID, instanceIndex, name, idOffset, count);
}

void modules::mixer::MixerControls::ctor(int32_t id, int32_t instanceIndex, std::string name, int32_t idOffset, int32_t count)
{
    super::ctor(id, instanceIndex, name);
    init();
    this->idOffset = idOffset;
    this->count = count;
    level = new ::floatArray(count);
    createControls();
    deriveSampleRateIndependentVariables();
    deriveSampleRateDependentVariables();
}

void modules::mixer::MixerControls::derive(ctoot::control::Control* c)
{
    auto n = c->getId() - idOffset - LEVEL;
    (*level)[n] = deriveLevel(n);
}

void modules::mixer::MixerControls::createControls()
{
    levelControl = new ctoot::control::FloatControlArray(count);
    for (auto i = int32_t(0); i < count; i++) {
        add(levelControl->set(i, createLevelControl(i)));
    }
}

void modules::mixer::MixerControls::deriveSampleRateIndependentVariables()
{
    for (auto i = int32_t(0); i < count; i++) {
        (*level)[i] = deriveLevel(i);
    }
}

float ctoot::synth::modules::mixer::MixerControls::deriveLevel(int32_t i)
{
    return npc((*levelControl)[i])->getValue();
}

void modules::mixer::MixerControls::deriveSampleRateDependentVariables()
{
}

uk::org::toot::control::FloatControl* ctoot::synth::modules::mixer::MixerControls::createLevelControl(int32_t i)
{
    auto control = new ctoot::control::FloatControl(i + LEVEL + idOffset, ::java::lang::String::valueOf(i + int32_t(1)), ctoot::control::LinearLaw::UNITY(), 0.01f, i > 0 ? 0.0f : 1.0f);
    control->setInsertColor(::java::awt::Color::BLACK());
    return control;
}

int32_t ctoot::synth::modules::mixer::MixerControls::getCount()
{
    return count;
}

float ctoot::synth::modules::mixer::MixerControls::getLevel(int32_t n)
{
    return (*level)[n];
}

extern java::lang::Class *class_(const char16_t *c, int n);

java::lang::Class* ctoot::synth::modules::mixer::MixerControls::class_()
{
    static ::java::lang::Class* c = ::class_("uk.org.toot.synth.modules.mixer.MixerControls", 45);
    return c;
}

java::lang::Class* ctoot::synth::modules::mixer::MixerControls::getClass0()
{
    return class_();
}

