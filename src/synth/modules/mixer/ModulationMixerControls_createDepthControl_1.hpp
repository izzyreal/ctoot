// Generated from /toot2/src/uk/org/toot/synth/modules/mixer/ModulationMixerControls.java

#pragma once

#include <fwd-toot2.hpp>
#include <java/io/fwd-toot2.hpp>
#include <java/lang/fwd-toot2.hpp>
#include <control/fwd-toot2.hpp>
#include <synth/modules/mixer/fwd-toot2.hpp>
#include <control/FloatControl.hpp>

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

struct default_init_tag;

namespace ctoot { namespace synth {modules::mixer::ModulationMixerControls_createDepthControl_1
    : public ctoot::control::FloatControl
{

public:
    typedef ctoot::control::FloatControl super;

private:
    ::java::lang::StringArray* presetNames {  };

public:
    ::java::lang::StringArray* getPresetNames() override;
    void applyPreset(std::string presetName) override;

    // Generated
    ModulationMixerControls_createDepthControl_1(ModulationMixerControls *ModulationMixerControls_this, int32_t id, std::string name, ctoot::control::ControlLaw* law, float precision, float initialValue);
    ModulationMixerControls_createDepthControl_1(ModulationMixerControls *ModulationMixerControls_this, int32_t id, std::string name, ctoot::control::ControlLaw* law, float precision, float initialValue, std::string minLabel, std::string midLabel, std::string maxLabel);
    static ::java::lang::Class *class_();

private:
    void init();
    ModulationMixerControls *ModulationMixerControls_this;
    virtual ::java::lang::Class* getClass0();
    friend class ModulationMixerControls;
};
