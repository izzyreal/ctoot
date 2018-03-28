// Generated from /toot2/src/uk/org/toot/synth/modules/mixer/ModulationMixerControls.java
#include <synth/modules/mixer/ModulationMixerControls_createDepthControl_1.hpp>

#include <java/io/Serializable.hpp>
#include <java/lang/ArrayStoreException.hpp>
#include <java/lang/CharSequence.hpp>
#include <java/lang/Comparable.hpp>
#include <java/lang/NullPointerException.hpp>
#include <java/lang/Object.hpp>
#include <java/lang/String.hpp>
#include <misc/Localisation.hpp>
#include <synth/modules/mixer/ModulationMixerControls.hpp>
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
} // java

template<typename T>
static T* npc(T* t)
{
    if(!t) throw new ::java::lang::NullPointerException();
    return t;
}

 ctoot::synth::modules::mixer::ModulationMixerControls_createDepthControl_1::ModulationMixerControls_createDepthControl_1(ModulationMixerControls *ModulationMixerControls_this, int32_t id, std::string name, ctoot::control::ControlLaw* law, float precision, float initialValue)
    : super(*static_cast< ::default_init_tag* >(0))
    , ModulationMixerControls_this(ModulationMixerControls_this)
{
    clinit();
    init();
    ctor(id, name, law, precision, initialValue);
}

 ctoot::synth::modules::mixer::ModulationMixerControls_createDepthControl_1::ModulationMixerControls_createDepthControl_1(ModulationMixerControls *ModulationMixerControls_this, int32_t id, std::string name, ctoot::control::ControlLaw* law, float precision, float initialValue, std::string minLabel, std::string midLabel, std::string maxLabel)
    : super(*static_cast< ::default_init_tag* >(0))
    , ModulationMixerControls_this(ModulationMixerControls_this)
{
    clinit();
    init();
    ctor(id, name, law, precision, initialValue, minLabel, midLabel, maxLabel);
}

void modules::mixer::ModulationMixerControls_createDepthControl_1::init()
{
    presetNames = (new ::java::lang::StringArray({ctoot::misc::Localisation::getString("Off")}));
}

java::lang::StringArray* ctoot::synth::modules::mixer::ModulationMixerControls_createDepthControl_1::getPresetNames()
{
    return presetNames;
}

void modules::mixer::ModulationMixerControls_createDepthControl_1::applyPreset(std::string presetName)
{
    if(npc(presetName)->equals(static_cast< ::java::lang::Object* >(ctoot::misc::Localisation::getString("Off")))) {
        setValue(0.0f);
    }
}

extern java::lang::Class *class_(const char16_t *c, int n);

java::lang::Class* ctoot::synth::modules::mixer::ModulationMixerControls_createDepthControl_1::class_()
{
    static ::java::lang::Class* c = ::class_("", 0);
    return c;
}

java::lang::Class* ctoot::synth::modules::mixer::ModulationMixerControls_createDepthControl_1::getClass0()
{
    return class_();
}

