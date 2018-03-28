// Generated from /toot2/src/uk/org/toot/synth/modules/mixer/ModulationMixerControls.java

#pragma once

#include <fwd-toot2.hpp>
#include <java/io/fwd-toot2.hpp>
#include <java/lang/fwd-toot2.hpp>
#include <java/util/fwd-toot2.hpp>
#include <control/fwd-toot2.hpp>
#include <synth/modules/mixer/fwd-toot2.hpp>
#include <control/CompoundControl.hpp>
#include <synth/modules/mixer/ModulationMixerVariables.hpp>

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

struct default_init_tag;

namespace ctoot { namespace synth {modules::mixer::ModulationMixerControls
    : public ctoot::control::CompoundControl
    , public virtual ModulationMixerVariables
{

public:
    typedef ctoot::control::CompoundControl super;
    static constexpr int32_t DEPTH { int32_t(0) };

private:
    ctoot::control::ControlLaw* law {  };
    ctoot::control::FloatControlArray* depthControl {  };
    ::floatArray* depth {  };
    int32_t idOffset {  };
    int32_t count {  };
protected:
    void ctor(int32_t instanceIndex, std::string name, int32_t idOffset, ::java::lang::StringArray* labels, bool bipolar);
    void ctor(int32_t instanceIndex, std::string name, int32_t idOffset, ::java::lang::StringArray* labels, bool bipolar, float range, std::string units);

protected:
    void derive(ctoot::control::Control* c) override;
    virtual void createControls(::java::lang::StringArray* labels);
    virtual void deriveSampleRateIndependentVariables();
    virtual float deriveDepth(int32_t i);
    virtual ctoot::control::FloatControl* createDepthControl(int32_t i, std::string label);

public:
    int32_t getCount() override;
    float getDepth(int32_t n) override;
    ::floatArray* getDepths() override;

    // Generated
    ModulationMixerControls(int32_t instanceIndex, std::string name, int32_t idOffset, ::java::lang::StringArray* labels, bool bipolar);
    ModulationMixerControls(int32_t instanceIndex, std::string name, int32_t idOffset, ::java::lang::StringArray* labels, bool bipolar, float range, std::string units);
protected:
    ModulationMixerControls(const ::default_init_tag&);


public:
    static ::java::lang::Class *class_();

private:
    void init();
    virtual ::java::lang::Class* getClass0();
    friend class ModulationMixerControls_createDepthControl_1;
};
