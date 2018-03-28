// Generated from /toot2/src/uk/org/toot/synth/modules/oscillator/DSFOscillatorControls.java
#include <synth/modules/oscillator/DSFOscillatorControls.hpp>

#include <java/awt/Color.hpp>
#include <java/lang/NullPointerException.hpp>
#include <java/lang/String.hpp>
#include <control/BooleanControl.hpp>
#include <control/Control.hpp>
#include <control/FloatControl.hpp>
#include <control/IntegerControl.hpp>
#include <control/IntegerLaw.hpp>
#include <control/LinearLaw.hpp>
#include <misc/Localisation.hpp>
#include <synth/modules/oscillator/OscillatorIds.hpp>

template<typename T>
static T* npc(T* t)
{
    if(!t) throw new ::java::lang::NullPointerException();
    return t;
}

 ctoot::synth::modules::oscillator::DSFOscillatorControls::DSFOscillatorControls(const ::default_init_tag&)
    : super(*static_cast< ::default_init_tag* >(0))
{
    clinit();
}

 ctoot::synth::modules::oscillator::DSFOscillatorControls::DSFOscillatorControls(int32_t instanceIndex, std::string name, int32_t idOffset) 
    : DSFOscillatorControls(*static_cast< ::default_init_tag* >(0))
{
    ctor(instanceIndex,name,idOffset);
}

constexpr int32_t ctoot::synth::modules::oscillator::DSFOscillatorControls::RATIO_N;

constexpr int32_t ctoot::synth::modules::oscillator::DSFOscillatorControls::RATIO_D;

constexpr int32_t ctoot::synth::modules::oscillator::DSFOscillatorControls::PARTIALS;

constexpr int32_t ctoot::synth::modules::oscillator::DSFOscillatorControls::ROLLOFF;

constexpr int32_t ctoot::synth::modules::oscillator::DSFOscillatorControls::WOLFRAM;

uk::org::toot::control::IntegerLaw*& ctoot::synth::modules::oscillator::DSFOscillatorControls::RATIO_LAW()
{
    clinit();
    return RATIO_LAW_;
}
uk::org::toot::control::IntegerLaw* ctoot::synth::modules::oscillator::DSFOscillatorControls::RATIO_LAW_;

uk::org::toot::control::IntegerLaw*& ctoot::synth::modules::oscillator::DSFOscillatorControls::PARTIAL_LAW()
{
    clinit();
    return PARTIAL_LAW_;
}
uk::org::toot::control::IntegerLaw* ctoot::synth::modules::oscillator::DSFOscillatorControls::PARTIAL_LAW_;

void modules::oscillator::DSFOscillatorControls::ctor(int32_t instanceIndex, std::string name, int32_t idOffset)
{
    super::ctor(OscillatorIds::DSF_OSCILLATOR_ID, instanceIndex, name);
    this->idOffset = idOffset;
    createControls();
    deriveSampleRateIndependentVariables();
}

void modules::oscillator::DSFOscillatorControls::derive(ctoot::control::Control* c)
{
    switch (c->getId() - idOffset) {
    case RATIO_N:
        ratioNumerator = deriveRatioNumerator();
        break;
    case RATIO_D:
        ratioDenominator = deriveRatioDenominator();
        break;
    case PARTIALS:
        partialCount = derivePartialCount();
        break;
    case ROLLOFF:
        rolloffFactor = deriveRolloffFactor();
        rolloffInt = deriveRolloffInt();
        break;
    case WOLFRAM:
        canUseWolfram_ = deriveWolfram();
        break;
    }

}

void modules::oscillator::DSFOscillatorControls::createControls()
{
    add(ratioNumeratorControl = createRatioControl(RATIO_N, u"N"));
    add(ratioDenominatorControl = createRatioControl(RATIO_D, u"D"));
    add(partialsControl = createPartialsControl(PARTIALS));
    add(rolloffControl = createRolloffControl(ROLLOFF));
}

uk::org::toot::control::IntegerControl* ctoot::synth::modules::oscillator::DSFOscillatorControls::createRatioControl(int32_t id, std::string name)
{
    auto control = new ctoot::control::IntegerControl(id + idOffset, name, RATIO_LAW_, 1.0f, int32_t(1));
    control->setInsertColor(::java::awt::Color::GREEN());
    return control;
}

uk::org::toot::control::IntegerControl* ctoot::synth::modules::oscillator::DSFOscillatorControls::createPartialsControl(int32_t id)
{
    auto control = new ctoot::control::IntegerControl(id + idOffset, ctoot::misc::Localisation::getString("Partials"), PARTIAL_LAW_, 1.0f, int32_t(10));
    control->setInsertColor(::java::awt::Color::LIGHT_GRAY());
    return control;
}

uk::org::toot::control::FloatControl* ctoot::synth::modules::oscillator::DSFOscillatorControls::createRolloffControl(int32_t id)
{
    auto control = new ctoot::control::FloatControl(id + idOffset, ctoot::misc::Localisation::getString("Tone"), ctoot::control::LinearLaw::UNITY(), 1.0f, 0.5f);
    control->setInsertColor(::java::awt::Color::WHITE());
    return control;
}

uk::org::toot::control::BooleanControl* ctoot::synth::modules::oscillator::DSFOscillatorControls::createWolframControl(int32_t id)
{
    auto control = new ctoot::control::BooleanControl(id, u"W", false);
    control->setStateColor(false, ::java::awt::Color::GREEN());
    control->setStateColor(true, ::java::awt::Color::YELLOW());
    return control;
}

void modules::oscillator::DSFOscillatorControls::deriveSampleRateIndependentVariables()
{
    ratioDenominator = deriveRatioDenominator();
    ratioNumerator = deriveRatioNumerator();
    partialCount = derivePartialCount();
    rolloffFactor = deriveRolloffFactor();
    canUseWolfram_ = deriveWolfram();
}

int32_t ctoot::synth::modules::oscillator::DSFOscillatorControls::deriveRatioDenominator()
{
    return npc(ratioDenominatorControl)->getUserValue();
}

int32_t ctoot::synth::modules::oscillator::DSFOscillatorControls::deriveRatioNumerator()
{
    return npc(ratioNumeratorControl)->getUserValue();
}

int32_t ctoot::synth::modules::oscillator::DSFOscillatorControls::derivePartialCount()
{
    return npc(partialsControl)->getUserValue();
}

float ctoot::synth::modules::oscillator::DSFOscillatorControls::deriveRolloffFactor()
{
    return npc(rolloffControl)->getValue() * 0.98f;
}

int32_t ctoot::synth::modules::oscillator::DSFOscillatorControls::deriveRolloffInt()
{
    return npc(rolloffControl)->getIntValue();
}

bool ctoot::synth::modules::oscillator::DSFOscillatorControls::deriveWolfram()
{
    if(wolframControl == nullptr)
        return false;

    return npc(wolframControl)->getValue();
}

int32_t ctoot::synth::modules::oscillator::DSFOscillatorControls::getPartialCount()
{
    return partialCount;
}

float ctoot::synth::modules::oscillator::DSFOscillatorControls::getPartialRolloffFactor()
{
    return rolloffFactor;
}

int32_t ctoot::synth::modules::oscillator::DSFOscillatorControls::getPartialRolloffInt()
{
    return rolloffInt;
}

int32_t ctoot::synth::modules::oscillator::DSFOscillatorControls::getRatioDenominator()
{
    return ratioDenominator;
}

int32_t ctoot::synth::modules::oscillator::DSFOscillatorControls::getRatioNumerator()
{
    return ratioNumerator;
}

bool ctoot::synth::modules::oscillator::DSFOscillatorControls::canUseWolfram()
{
    return canUseWolfram_;
}

extern java::lang::Class *class_(const char16_t *c, int n);

java::lang::Class* ctoot::synth::modules::oscillator::DSFOscillatorControls::class_()
{
    static ::java::lang::Class* c = ::class_("uk.org.toot.synth.modules.oscillator.DSFOscillatorControls", 58);
    return c;
}

void modules::oscillator::DSFOscillatorControls::clinit()
{
    super::clinit();
    static bool in_cl_init = false;
struct clinit_ {
    clinit_() {
        in_cl_init = true;
        RATIO_LAW_ = new ctoot::control::IntegerLaw(int32_t(1), int32_t(9), u"");
        PARTIAL_LAW_ = new ctoot::control::IntegerLaw(int32_t(1), int32_t(200), u"");
    }
};

    if(!in_cl_init) {
        static clinit_ clinit_instance;
    }
}

java::lang::Class* ctoot::synth::modules::oscillator::DSFOscillatorControls::getClass0()
{
    return class_();
}

