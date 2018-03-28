// Generated from /toot2/src/uk/org/toot/synth/modules/oscillator/LFOControls.java
#include <synth/modules/oscillator/LFOControls.hpp>

#include <java/lang/NullPointerException.hpp>
#include <java/lang/Object.hpp>
#include <java/lang/String.hpp>
#include <java/util/ArrayList.hpp>
#include <java/util/List.hpp>
#include <control/Control.hpp>
#include <control/EnumControl.hpp>
#include <control/FloatControl.hpp>
#include <control/LinearLaw.hpp>
#include <control/LogLaw.hpp>
#include <misc/Localisation.hpp>
#include <synth/modules/oscillator/LFOConfig.hpp>
#include <synth/modules/oscillator/LFOControls_createShapeControl_1.hpp>
#include <synth/modules/oscillator/OscillatorIds.hpp>

template<typename T>
static T* npc(T* t)
{
    if(!t) throw new ::java::lang::NullPointerException();
    return t;
}

 ctoot::synth::modules::oscillator::LFOControls::LFOControls(const ::default_init_tag&)
    : super(*static_cast< ::default_init_tag* >(0))
{
    clinit();
}

 ctoot::synth::modules::oscillator::LFOControls::LFOControls(int32_t instanceIndex, std::string name, int32_t idOffset, LFOConfig* cfg) 
    : LFOControls(*static_cast< ::default_init_tag* >(0))
{
    ctor(instanceIndex,name,idOffset,cfg);
}

 ctoot::synth::modules::oscillator::LFOControls::LFOControls(int32_t id, int32_t instanceIndex, std::string name, int32_t idOffset, LFOConfig* cfg) 
    : LFOControls(*static_cast< ::default_init_tag* >(0))
{
    ctor(id,instanceIndex,name,idOffset,cfg);
}

constexpr int32_t ctoot::synth::modules::oscillator::LFOControls::FREQUENCY;

constexpr int32_t ctoot::synth::modules::oscillator::LFOControls::DEVIATION;

constexpr int32_t ctoot::synth::modules::oscillator::LFOControls::SHAPE;

void modules::oscillator::LFOControls::ctor(int32_t instanceIndex, std::string name, int32_t idOffset, LFOConfig* cfg)
{
    ctor(OscillatorIds::LFO_ID, instanceIndex, name, idOffset, cfg);
}

void modules::oscillator::LFOControls::ctor(int32_t id, int32_t instanceIndex, std::string name, int32_t idOffset, LFOConfig* cfg)
{
    super::ctor(id, instanceIndex, name);
    this->idOffset = idOffset;
    config = cfg;
    createControls();
    deriveSampleRateIndependentVariables();
    deriveSampleRateDependentVariables();
}

void modules::oscillator::LFOControls::derive(ctoot::control::Control* c)
{
    switch (c->getId() - idOffset) {
    case FREQUENCY:
        frequency = deriveFrequency();
        break;
    case DEVIATION:
        deviation = deriveDeviation();
        break;
    case SHAPE:
        sine = deriveShape();
        break;
    }

}

void modules::oscillator::LFOControls::createControls()
{
    add(shapeControl = createShapeControl());
    derive(static_cast< ctoot::control::Control* >(shapeControl));
    add(frequencyControl = createFrequencyControl());
    derive(static_cast< ctoot::control::Control* >(frequencyControl));
    if(config->deviation > 0) {
        add(deviationControl = createDeviationControl());
        derive(static_cast< ctoot::control::Control* >(deviationControl));
    }
}

uk::org::toot::control::EnumControl* ctoot::synth::modules::oscillator::LFOControls::createShapeControl()
{
    ::java::util::List* const shapeNames = new ::java::util::ArrayList();
    npc(shapeNames)->add(static_cast< ::java::lang::Object* >("Sine"));
    npc(shapeNames)->add(static_cast< ::java::lang::Object* >("Triangle"));
    return new LFOControls_createShapeControl_1(this, shapeNames, SHAPE + idOffset, u"Shape", u"Sine");
}

uk::org::toot::control::FloatControl* ctoot::synth::modules::oscillator::LFOControls::createFrequencyControl()
{
    ctoot::control::ControlLaw* law = new ctoot::control::LogLaw(config->rateMin, config->rateMax, u"Hz");
    auto control = new ctoot::control::FloatControl(FREQUENCY + idOffset, ctoot::misc::Localisation::getString("Frequency"), law, 0.1f, config->rate);
    return control;
}

uk::org::toot::control::FloatControl* ctoot::synth::modules::oscillator::LFOControls::createDeviationControl()
{
    ctoot::control::ControlLaw* law = new ctoot::control::LinearLaw(0.0f, config->deviationMax, u"Hz");
    auto control = new ctoot::control::FloatControl(FREQUENCY + idOffset, ctoot::misc::Localisation::getString("Deviation"), law, 0.1f, config->deviation);
    return control;
}

void modules::oscillator::LFOControls::deriveSampleRateIndependentVariables()
{
    frequency = deriveFrequency();
    deviation = deriveDeviation();
    sine = deriveShape();
}

void modules::oscillator::LFOControls::deriveSampleRateDependentVariables()
{
}

float ctoot::synth::modules::oscillator::LFOControls::deriveFrequency()
{
    return npc(frequencyControl)->getValue();
}

float ctoot::synth::modules::oscillator::LFOControls::deriveDeviation()
{
    if(deviationControl == nullptr)
        return 0.0f;

    return npc(deviationControl)->getValue();
}

bool ctoot::synth::modules::oscillator::LFOControls::deriveShape()
{
    return npc(npc(shapeControl)->getValue())->equals("Sine");
}

float ctoot::synth::modules::oscillator::LFOControls::getFrequency()
{
    return frequency;
}

float ctoot::synth::modules::oscillator::LFOControls::getDeviation()
{
    return deviation;
}

bool ctoot::synth::modules::oscillator::LFOControls::isSine()
{
    return sine;
}

extern java::lang::Class *class_(const char16_t *c, int n);

java::lang::Class* ctoot::synth::modules::oscillator::LFOControls::class_()
{
    static ::java::lang::Class* c = ::class_("uk.org.toot.synth.modules.oscillator.LFOControls", 48);
    return c;
}

java::lang::Class* ctoot::synth::modules::oscillator::LFOControls::getClass0()
{
    return class_();
}

