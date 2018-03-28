// Generated from /toot2/src/uk/org/toot/synth/modules/GlideControls.java

#pragma once

#include <fwd-toot2.hpp>
#include <java/lang/fwd-toot2.hpp>
#include <control/fwd-toot2.hpp>
#include <synth/modules/fwd-toot2.hpp>
#include <control/CompoundControl.hpp>
#include <synth/modules/GlideVariables.hpp>

struct default_init_tag;

namespace ctoot { namespace synth {modules::GlideControls
    : public ctoot::control::CompoundControl
    , public virtual GlideVariables
{

public:
    typedef ctoot::control::CompoundControl super;

private:
    static ctoot::control::ControlLaw* TIME_LAW_;

public:
    static constexpr int32_t ENABLE { int32_t(0) };
    static constexpr int32_t TIME { int32_t(1) };

private:
    ctoot::control::FloatControl* timeControl {  };
    ctoot::control::BooleanControl* enableControl {  };
    int32_t glideMillis {  };
    bool glideEnable {  };
    int32_t idOffset {  };
protected:
    void ctor(int32_t idOffset);
    void ctor(int32_t id, std::string name, int32_t idOffset);

protected:
    void derive(ctoot::control::Control* c) override;
    virtual void createControls();
    virtual void deriveSampleRateIndependentVariables();
    virtual bool deriveEnable();
    virtual int32_t deriveTime();
    virtual ctoot::control::BooleanControl* createEnableControl();
    virtual ctoot::control::FloatControl* createTimeControl();

public:
    int32_t getGlideMilliseconds() override;
    bool isGlideEnabled() override;

    // Generated
    GlideControls(int32_t idOffset);
    GlideControls(int32_t id, std::string name, int32_t idOffset);
protected:
    GlideControls(const ::default_init_tag&);


public:
    static ::java::lang::Class *class_();
    static void clinit();

private:
    void init();
    static ctoot::control::ControlLaw*& TIME_LAW();
    virtual ::java::lang::Class* getClass0();
};
