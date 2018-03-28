// Generated from /toot2/src/uk/org/toot/synth/modules/oscillator/UnisonControls.java
#include <synth/modules/oscillator/UnisonControls.hpp>

#include <java/awt/Color.hpp>
#include <java/lang/NullPointerException.hpp>
#include <java/lang/String.hpp>
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

 ctoot::synth::modules::oscillator::UnisonControls::UnisonControls(const ::default_init_tag&)
    : super(*static_cast< ::default_init_tag* >(0))
{
    clinit();
}

 ctoot::synth::modules::oscillator::UnisonControls::UnisonControls(int32_t idOffset) 
    : UnisonControls(*static_cast< ::default_init_tag* >(0))
{
    ctor(idOffset);
}

constexpr int32_t ctoot::synth::modules::oscillator::UnisonControls::OSC_COUNT;

constexpr int32_t ctoot::synth::modules::oscillator::UnisonControls::PITCH_SPREAD;

constexpr int32_t ctoot::synth::modules::oscillator::UnisonControls::PHASE_SPREAD;

uk::org::toot::control::IntegerLaw*& ctoot::synth::modules::oscillator::UnisonControls::OSC_COUNT_LAW()
{
    clinit();
    return OSC_COUNT_LAW_;
}
uk::org::toot::control::IntegerLaw* ctoot::synth::modules::oscillator::UnisonControls::OSC_COUNT_LAW_;

uk::org::toot::control::LinearLaw*& ctoot::synth::modules::oscillator::UnisonControls::SPREAD_LAW()
{
    clinit();
    return SPREAD_LAW_;
}
uk::org::toot::control::LinearLaw* ctoot::synth::modules::oscillator::UnisonControls::SPREAD_LAW_;

void modules::oscillator::UnisonControls::ctor(int32_t idOffset)
{
    super::ctor(OscillatorIds::UNISON_ID, int32_t(0), ctoot::misc::Localisation::getString("Unison"));
    this->idOffset = idOffset;
    createControls();
    deriveSampleRateIndependentVariables();
}

void modules::oscillator::UnisonControls::derive(ctoot::control::Control* c)
{
    switch (c->getId() - idOffset) {
    case OSC_COUNT:
        oscillatorCount = deriveOscillatorCount();
        break;
    case PITCH_SPREAD:
        pitchSpread = derivePitchSpread();
        break;
    case PHASE_SPREAD:
        phaseSpread = derivePhaseSpread();
        break;
    }

}

void modules::oscillator::UnisonControls::createControls()
{
    add(oscillatorCountControl = createOscillatorCountControl());
    add(pitchSpreadControl = createPitchSpreadControl());
    add(phaseSpreadControl = createPhaseSpreadControl());
    derive(static_cast< ctoot::control::Control* >(oscillatorCountControl));
    derive(static_cast< ctoot::control::Control* >(pitchSpreadControl));
    derive(static_cast< ctoot::control::Control* >(phaseSpreadControl));
}

uk::org::toot::control::IntegerControl* ctoot::synth::modules::oscillator::UnisonControls::createOscillatorCountControl()
{
    auto control = new ctoot::control::IntegerControl(OSC_COUNT + idOffset, ctoot::misc::Localisation::getString("Oscs"), OSC_COUNT_LAW_, 1.0f, int32_t(1));
    control->setInsertColor(npc(::java::awt::Color::CYAN())->darker());
    return control;
}

uk::org::toot::control::FloatControl* ctoot::synth::modules::oscillator::UnisonControls::createPitchSpreadControl()
{
    auto control = new ctoot::control::FloatControl(PITCH_SPREAD + idOffset, ctoot::misc::Localisation::getString("Detune"), SPREAD_LAW_, 0.01f, 0.0f);
    control->setInsertColor(npc(::java::awt::Color::MAGENTA())->darker());
    return control;
}

uk::org::toot::control::FloatControl* ctoot::synth::modules::oscillator::UnisonControls::createPhaseSpreadControl()
{
    auto control = new ctoot::control::FloatControl(PHASE_SPREAD + idOffset, ctoot::misc::Localisation::getString("Phase"), SPREAD_LAW_, 0.01f, 1.0f);
    control->setInsertColor(::java::awt::Color::BLUE());
    return control;
}

void modules::oscillator::UnisonControls::deriveSampleRateIndependentVariables()
{
    oscillatorCount = deriveOscillatorCount();
    pitchSpread = derivePitchSpread();
    phaseSpread = derivePhaseSpread();
}

int32_t ctoot::synth::modules::oscillator::UnisonControls::deriveOscillatorCount()
{
    return npc(oscillatorCountControl)->getUserValue();
}

float ctoot::synth::modules::oscillator::UnisonControls::derivePitchSpread()
{
    return npc(pitchSpreadControl)->getValue();
}

float ctoot::synth::modules::oscillator::UnisonControls::derivePhaseSpread()
{
    return npc(phaseSpreadControl)->getValue();
}

int32_t ctoot::synth::modules::oscillator::UnisonControls::getOscillatorCount()
{
    return oscillatorCount;
}

float ctoot::synth::modules::oscillator::UnisonControls::getPitchSpread()
{
    return pitchSpread;
}

float ctoot::synth::modules::oscillator::UnisonControls::getPhaseSpread()
{
    return phaseSpread;
}

extern java::lang::Class *class_(const char16_t *c, int n);

java::lang::Class* ctoot::synth::modules::oscillator::UnisonControls::class_()
{
    static ::java::lang::Class* c = ::class_("uk.org.toot.synth.modules.oscillator.UnisonControls", 51);
    return c;
}

void modules::oscillator::UnisonControls::clinit()
{
    super::clinit();
    static bool in_cl_init = false;
struct clinit_ {
    clinit_() {
        in_cl_init = true;
        OSC_COUNT_LAW_ = new ctoot::control::IntegerLaw(int32_t(1), int32_t(32), u"");
        SPREAD_LAW_ = ctoot::control::LinearLaw::UNITY();
    }
};

    if(!in_cl_init) {
        static clinit_ clinit_instance;
    }
}

java::lang::Class* ctoot::synth::modules::oscillator::UnisonControls::getClass0()
{
    return class_();
}

