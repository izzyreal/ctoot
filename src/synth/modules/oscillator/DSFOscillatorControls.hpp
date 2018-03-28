// Generated from /toot2/src/uk/org/toot/synth/modules/oscillator/DSFOscillatorControls.java

#pragma once

#include <fwd-toot2.hpp>
#include <java/lang/fwd-toot2.hpp>
#include <control/fwd-toot2.hpp>
#include <synth/modules/oscillator/fwd-toot2.hpp>
#include <control/CompoundControl.hpp>
#include <synth/modules/oscillator/DSFOscillatorVariables.hpp>

struct default_init_tag;

namespace ctoot { namespace synth {modules::oscillator::DSFOscillatorControls
    : public ctoot::control::CompoundControl
    , public virtual DSFOscillatorVariables
{

public:
    typedef ctoot::control::CompoundControl super;
    static constexpr int32_t RATIO_N { int32_t(0) };
    static constexpr int32_t RATIO_D { int32_t(1) };
    static constexpr int32_t PARTIALS { int32_t(2) };
    static constexpr int32_t ROLLOFF { int32_t(3) };
    static constexpr int32_t WOLFRAM { int32_t(4) };

private:
    static ctoot::control::IntegerLaw* RATIO_LAW_;
    static ctoot::control::IntegerLaw* PARTIAL_LAW_;
    ctoot::control::IntegerControl* ratioNumeratorControl {  };
    ctoot::control::IntegerControl* ratioDenominatorControl {  };
    ctoot::control::IntegerControl* partialsControl {  };
    ctoot::control::FloatControl* rolloffControl {  };
    ctoot::control::BooleanControl* wolframControl {  };
    int32_t idOffset {  };
    int32_t ratioNumerator {  };
    int32_t ratioDenominator {  };
    int32_t partialCount {  };
    float rolloffFactor {  };
    int32_t rolloffInt {  };
    bool canUseWolfram_ {  };
protected:
    void ctor(int32_t instanceIndex, std::string name, int32_t idOffset);

protected:
    void derive(ctoot::control::Control* c) override;

private:
    void createControls();

protected:
    virtual ctoot::control::IntegerControl* createRatioControl(int32_t id, std::string name);
    virtual ctoot::control::IntegerControl* createPartialsControl(int32_t id);
    virtual ctoot::control::FloatControl* createRolloffControl(int32_t id);
    virtual ctoot::control::BooleanControl* createWolframControl(int32_t id);

private:
    void deriveSampleRateIndependentVariables();

protected:
    virtual int32_t deriveRatioDenominator();
    virtual int32_t deriveRatioNumerator();
    virtual int32_t derivePartialCount();
    virtual float deriveRolloffFactor();
    virtual int32_t deriveRolloffInt();
    virtual bool deriveWolfram();

public:
    int32_t getPartialCount() override;
    float getPartialRolloffFactor() override;
    int32_t getPartialRolloffInt() override;
    int32_t getRatioDenominator() override;
    int32_t getRatioNumerator() override;
    bool canUseWolfram() override;

    // Generated
    DSFOscillatorControls(int32_t instanceIndex, std::string name, int32_t idOffset);
protected:
    DSFOscillatorControls(const ::default_init_tag&);


public:
    static ::java::lang::Class *class_();
    static void clinit();

private:
    static ctoot::control::IntegerLaw*& RATIO_LAW();
    static ctoot::control::IntegerLaw*& PARTIAL_LAW();
    virtual ::java::lang::Class* getClass0();
};
