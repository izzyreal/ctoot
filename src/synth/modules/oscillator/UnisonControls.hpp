// Generated from /toot2/src/uk/org/toot/synth/modules/oscillator/UnisonControls.java

#pragma once

#include <fwd-toot2.hpp>
#include <control/fwd-toot2.hpp>
#include <synth/modules/oscillator/fwd-toot2.hpp>
#include <control/CompoundControl.hpp>
#include <synth/modules/oscillator/UnisonVariables.hpp>

struct default_init_tag;

namespace ctoot { namespace synth {modules::oscillator::UnisonControls
    : public ctoot::control::CompoundControl
    , public virtual UnisonVariables
{

public:
    typedef ctoot::control::CompoundControl super;
    static constexpr int32_t OSC_COUNT { int32_t(0) };
    static constexpr int32_t PITCH_SPREAD { int32_t(1) };
    static constexpr int32_t PHASE_SPREAD { int32_t(2) };

private:
    static ctoot::control::IntegerLaw* OSC_COUNT_LAW_;
    static ctoot::control::LinearLaw* SPREAD_LAW_;
    ctoot::control::IntegerControl* oscillatorCountControl {  };
    ctoot::control::FloatControl* pitchSpreadControl {  };
    ctoot::control::FloatControl* phaseSpreadControl {  };
    int32_t idOffset {  };
    int32_t oscillatorCount {  };
    float pitchSpread {  };
    float phaseSpread {  };
protected:
    void ctor(int32_t idOffset);

protected:
    void derive(ctoot::control::Control* c) override;

private:
    void createControls();

protected:
    virtual ctoot::control::IntegerControl* createOscillatorCountControl();
    virtual ctoot::control::FloatControl* createPitchSpreadControl();
    virtual ctoot::control::FloatControl* createPhaseSpreadControl();

private:
    void deriveSampleRateIndependentVariables();

protected:
    virtual int32_t deriveOscillatorCount();
    virtual float derivePitchSpread();
    virtual float derivePhaseSpread();

public:
    int32_t getOscillatorCount() override;
    float getPitchSpread() override;
    float getPhaseSpread() override;

    // Generated
    UnisonControls(int32_t idOffset);
protected:
    UnisonControls(const ::default_init_tag&);


public:
    static ::java::lang::Class *class_();
    static void clinit();

private:
    static ctoot::control::IntegerLaw*& OSC_COUNT_LAW();
    static ctoot::control::LinearLaw*& SPREAD_LAW();
    virtual ::java::lang::Class* getClass0();
};
