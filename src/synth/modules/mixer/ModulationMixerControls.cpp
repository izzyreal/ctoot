// Generated from /toot2/src/uk/org/toot/synth/modules/mixer/ModulationMixerControls.java
#include <synth/modules/mixer/ModulationMixerControls.hpp>

#include <java/awt/Color.hpp>
#include <java/io/Serializable.hpp>
#include <java/lang/ArrayStoreException.hpp>
#include <java/lang/CharSequence.hpp>
#include <java/lang/Comparable.hpp>
#include <java/lang/NullPointerException.hpp>
#include <java/lang/String.hpp>
#include <java/util/Observable.hpp>
#include <control/Control.hpp>
#include <control/FloatControl.hpp>
#include <control/LawControl.hpp>
#include <control/LinearLaw.hpp>
#include <synth/modules/mixer/MixerIds.hpp>
#include <synth/modules/mixer/ModulationMixerControls_createDepthControl_1.hpp>
#include <Array.hpp>
#include <SubArray.hpp>
#include <ObjectArray.hpp>

template<typename ComponentType, typename... Bases> struct SubArray;
namespace java
{
    namespace io
    {
typedef ::SubArray< ::java::io::Serializable, ::java::lang::ObjectArray > SerializableArray;
    } // io

    namespace lang
    {
typedef ::SubArray< ::java::lang::CharSequence, ObjectArray > CharSequenceArray;
typedef ::SubArray< ::java::lang::Comparable, ObjectArray > ComparableArray;
typedef ::SubArray< ::java::lang::String, ObjectArray, ::java::io::SerializableArray, ComparableArray, CharSequenceArray > StringArray;
    } // lang

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

 ctoot::synth::modules::mixer::ModulationMixerControls::ModulationMixerControls(const ::default_init_tag&)
    : super(*static_cast< ::default_init_tag* >(0))
{
    clinit();
}

 ctoot::synth::modules::mixer::ModulationMixerControls::ModulationMixerControls(int32_t instanceIndex, std::string name, int32_t idOffset, ::java::lang::StringArray* labels, bool bipolar) 
    : ModulationMixerControls(*static_cast< ::default_init_tag* >(0))
{
    ctor(instanceIndex,name,idOffset,labels,bipolar);
}

 ctoot::synth::modules::mixer::ModulationMixerControls::ModulationMixerControls(int32_t instanceIndex, std::string name, int32_t idOffset, ::java::lang::StringArray* labels, bool bipolar, float range, std::string units) 
    : ModulationMixerControls(*static_cast< ::default_init_tag* >(0))
{
    ctor(instanceIndex,name,idOffset,labels,bipolar,range,units);
}

void modules::mixer::ModulationMixerControls::init()
{
    idOffset = int32_t(0);
}

constexpr int32_t ctoot::synth::modules::mixer::ModulationMixerControls::DEPTH;

void modules::mixer::ModulationMixerControls::ctor(int32_t instanceIndex, std::string name, int32_t idOffset, ::java::lang::StringArray* labels, bool bipolar)
{
    ctor(instanceIndex, name, idOffset, labels, bipolar, 1.0f, u"");
}

void modules::mixer::ModulationMixerControls::ctor(int32_t instanceIndex, std::string name, int32_t idOffset, ::java::lang::StringArray* labels, bool bipolar, float range, std::string units)
{
    super::ctor(MixerIds::MODULATION_MIXER_ID, instanceIndex, name);
    init();
    this->idOffset = idOffset;
    this->count = npc(labels)->length;
    law = new ctoot::control::LinearLaw(bipolar ? -range : 0.0f, range, units);
    depth = new ::floatArray(count);
    createControls(labels);
    deriveSampleRateIndependentVariables();
}

void modules::mixer::ModulationMixerControls::derive(ctoot::control::Control* c)
{
    auto n = c->getId() - idOffset - DEPTH;
    (*depth)[n] = deriveDepth(n);
}

void modules::mixer::ModulationMixerControls::createControls(::java::lang::StringArray* labels)
{
    depthControl = new ctoot::control::FloatControlArray(count);
    for (auto i = int32_t(0); i < count; i++) {
        add(depthControl->set(i, createDepthControl(i, (*labels)[i])));
    }
}

void modules::mixer::ModulationMixerControls::deriveSampleRateIndependentVariables()
{
    for (auto i = int32_t(0); i < count; i++) {
        (*depth)[i] = deriveDepth(i);
    }
}

float ctoot::synth::modules::mixer::ModulationMixerControls::deriveDepth(int32_t i)
{
    return npc((*depthControl)[i])->getValue();
}

uk::org::toot::control::FloatControl* ctoot::synth::modules::mixer::ModulationMixerControls::createDepthControl(int32_t i, std::string label)
{
    ctoot::control::FloatControl* control = new ModulationMixerControls_createDepthControl_1(this, i + DEPTH + idOffset, label, law, 0.01f, 0.0f);
    control->setInsertColor(::java::awt::Color::DARK_GRAY());
    return control;
}

int32_t ctoot::synth::modules::mixer::ModulationMixerControls::getCount()
{
    return count;
}

float ctoot::synth::modules::mixer::ModulationMixerControls::getDepth(int32_t n)
{
    return (*depth)[n];
}

floatArray* ctoot::synth::modules::mixer::ModulationMixerControls::getDepths()
{
    return depth;
}

extern java::lang::Class *class_(const char16_t *c, int n);

java::lang::Class* ctoot::synth::modules::mixer::ModulationMixerControls::class_()
{
    static ::java::lang::Class* c = ::class_("uk.org.toot.synth.modules.mixer.ModulationMixerControls", 55);
    return c;
}

java::lang::Class* ctoot::synth::modules::mixer::ModulationMixerControls::getClass0()
{
    return class_();
}

