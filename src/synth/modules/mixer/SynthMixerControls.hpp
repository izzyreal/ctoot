// Generated from /toot2/src/uk/org/toot/synth/modules/mixer/MixerControls.java

#pragma once

#include <fwd-toot2.hpp>
#include <java/lang/fwd-toot2.hpp>
#include <java/util/fwd-toot2.hpp>
#include <control/fwd-toot2.hpp>
#include <synth/modules/mixer/fwd-toot2.hpp>
#include <control/CompoundControl.hpp>
#include <synth/modules/mixer/MixerVariables.hpp>

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

struct default_init_tag;

namespace ctoot { namespace synth {modules::mixer::MixerControls
    : public ctoot::control::CompoundControl
    , public virtual MixerVariables
{

public:
    typedef ctoot::control::CompoundControl super;
    static constexpr int32_t LEVEL { int32_t(0) };

private:
    ctoot::control::FloatControlArray* levelControl {  };
    ::floatArray* level {  };
    int32_t idOffset {  };
    int32_t count {  };
protected:
    void ctor(int32_t instanceIndex, std::string name, int32_t idOffset, int32_t count);
    void ctor(int32_t id, int32_t instanceIndex, std::string name, int32_t idOffset, int32_t count);

protected:
    void derive(ctoot::control::Control* c) override;
    virtual void createControls();
    virtual void deriveSampleRateIndependentVariables();
    virtual float deriveLevel(int32_t i);
    virtual void deriveSampleRateDependentVariables();
    virtual ctoot::control::FloatControl* createLevelControl(int32_t i);

public:
    int32_t getCount() override;
    float getLevel(int32_t n) override;

    // Generated
    MixerControls(int32_t instanceIndex, std::string name, int32_t idOffset, int32_t count);
    MixerControls(int32_t id, int32_t instanceIndex, std::string name, int32_t idOffset, int32_t count);
protected:
    MixerControls(const ::default_init_tag&);


public:
    static ::java::lang::Class *class_();

private:
    void init();
    virtual ::java::lang::Class* getClass0();
};
