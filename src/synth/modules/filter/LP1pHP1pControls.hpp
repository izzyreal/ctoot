// Generated from /toot2/src/uk/org/toot/synth/modules/filter/LP1pHP1pControls.java

#pragma once

#include <fwd-toot2.hpp>
#include <java/lang/fwd-toot2.hpp>
#include <control/fwd-toot2.hpp>
#include <synth/modules/filter/fwd-toot2.hpp>
#include <control/CompoundControl.hpp>
#include <synth/modules/filter/LP1pHP1pVariables.hpp>

struct default_init_tag;

namespace ctoot { namespace synth {modules::filter::LP1pHP1pControls
    : public ctoot::control::CompoundControl
    , public virtual LP1pHP1pVariables
{

public:
    typedef ctoot::control::CompoundControl super;

private:
    static ctoot::control::ControlLaw* LP_LAW_;
    static ctoot::control::ControlLaw* HP_LAW_;
    static constexpr int32_t LPRATIO { int32_t(0) };
    static constexpr int32_t HPRATIO { int32_t(1) };
    ctoot::control::FloatControl* lpRatioControl {  };
    ctoot::control::FloatControl* hpRatioControl {  };
    float hpRatio {  }, lpRatio {  };

protected:
    int32_t idOffset {  };

private:
    int32_t sampleRate {  };
protected:
    void ctor(int32_t id, int32_t instanceIndex, std::string name, int32_t idOffset);

protected:
    void derive(ctoot::control::Control* c) override;
    virtual void createControls();
    virtual void deriveSampleRateIndependentVariables();
    virtual void deriveSampleRateDependentVariables();
    virtual float deriveLPRatio();
    virtual float deriveHPRatio();
    virtual ctoot::control::FloatControl* createLPRatioControl();
    virtual ctoot::control::FloatControl* createHPRatioControl();

public:
    virtual void setSampleRate(int32_t rate);
    float getHighPassRatio() override;
    float getLowPassRatio() override;

    // Generated
    LP1pHP1pControls(int32_t id, int32_t instanceIndex, std::string name, int32_t idOffset);
protected:
    LP1pHP1pControls(const ::default_init_tag&);


public:
    static ::java::lang::Class *class_();
    static void clinit();

private:
    void init();
    static ctoot::control::ControlLaw*& LP_LAW();
    static ctoot::control::ControlLaw*& HP_LAW();
    virtual ::java::lang::Class* getClass0();
};
