// Generated from /toot2/src/uk/org/toot/synth/modules/filter/LP1pHP1pControls.java
#include <synth/modules/filter/LP1pHP1pControls.hpp>

#include <java/awt/Color.hpp>
#include <java/lang/NullPointerException.hpp>
#include <java/lang/String.hpp>
#include <control/Control.hpp>
#include <control/FloatControl.hpp>
#include <control/LogLaw.hpp>
#include <misc/Localisation.hpp>

template<typename T>
static T* npc(T* t)
{
    if(!t) throw new ::java::lang::NullPointerException();
    return t;
}

 ctoot::synth::modules::filter::LP1pHP1pControls::LP1pHP1pControls(const ::default_init_tag&)
    : super(*static_cast< ::default_init_tag* >(0))
{
    clinit();
}

 ctoot::synth::modules::filter::LP1pHP1pControls::LP1pHP1pControls(int32_t id, int32_t instanceIndex, std::string name, int32_t idOffset) 
    : LP1pHP1pControls(*static_cast< ::default_init_tag* >(0))
{
    ctor(id,instanceIndex,name,idOffset);
}

void modules::filter::LP1pHP1pControls::init()
{
    idOffset = int32_t(0);
    sampleRate = int32_t(44100);
}

uk::org::toot::control::ControlLaw*& ctoot::synth::modules::filter::LP1pHP1pControls::LP_LAW()
{
    clinit();
    return LP_LAW_;
}
uk::org::toot::control::ControlLaw* ctoot::synth::modules::filter::LP1pHP1pControls::LP_LAW_;

uk::org::toot::control::ControlLaw*& ctoot::synth::modules::filter::LP1pHP1pControls::HP_LAW()
{
    clinit();
    return HP_LAW_;
}
uk::org::toot::control::ControlLaw* ctoot::synth::modules::filter::LP1pHP1pControls::HP_LAW_;

constexpr int32_t ctoot::synth::modules::filter::LP1pHP1pControls::LPRATIO;

constexpr int32_t ctoot::synth::modules::filter::LP1pHP1pControls::HPRATIO;

void modules::filter::LP1pHP1pControls::ctor(int32_t id, int32_t instanceIndex, std::string name, int32_t idOffset)
{
    super::ctor(id, instanceIndex, name);
    init();
    this->idOffset = idOffset;
    createControls();
    deriveSampleRateIndependentVariables();
    deriveSampleRateDependentVariables();
}

void modules::filter::LP1pHP1pControls::derive(ctoot::control::Control* c)
{
    switch (c->getId() - idOffset) {
    case LPRATIO:
        lpRatio = deriveLPRatio();
        break;
    case HPRATIO:
        hpRatio = deriveHPRatio();
        break;
    }

}

void modules::filter::LP1pHP1pControls::createControls()
{
    add(lpRatioControl = createLPRatioControl());
    add(hpRatioControl = createHPRatioControl());
}

void modules::filter::LP1pHP1pControls::deriveSampleRateIndependentVariables()
{
    lpRatio = deriveLPRatio();
    hpRatio = deriveHPRatio();
}

void modules::filter::LP1pHP1pControls::deriveSampleRateDependentVariables()
{
}

float ctoot::synth::modules::filter::LP1pHP1pControls::deriveLPRatio()
{
    return npc(lpRatioControl)->getValue();
}

float ctoot::synth::modules::filter::LP1pHP1pControls::deriveHPRatio()
{
    return npc(hpRatioControl)->getValue();
}

uk::org::toot::control::FloatControl* ctoot::synth::modules::filter::LP1pHP1pControls::createLPRatioControl()
{
    auto control = new ctoot::control::FloatControl(LPRATIO + idOffset, ctoot::misc::Localisation::getString("LP"), LP_LAW_, 1.0f, int32_t(4));
    control->setInsertColor(::java::awt::Color::yellow());
    return control;
}

uk::org::toot::control::FloatControl* ctoot::synth::modules::filter::LP1pHP1pControls::createHPRatioControl()
{
    auto control = new ctoot::control::FloatControl(HPRATIO + idOffset, ctoot::misc::Localisation::getString("HP"), HP_LAW_, 0.1f, 1.0f);
    control->setInsertColor(::java::awt::Color::yellow());
    return control;
}

void modules::filter::LP1pHP1pControls::setSampleRate(int32_t rate)
{
    if(sampleRate != rate) {
        sampleRate = rate;
        deriveSampleRateDependentVariables();
    }
}

float ctoot::synth::modules::filter::LP1pHP1pControls::getHighPassRatio()
{
    return hpRatio;
}

float ctoot::synth::modules::filter::LP1pHP1pControls::getLowPassRatio()
{
    return lpRatio;
}

extern java::lang::Class *class_(const char16_t *c, int n);

java::lang::Class* ctoot::synth::modules::filter::LP1pHP1pControls::class_()
{
    static ::java::lang::Class* c = ::class_("uk.org.toot.synth.modules.filter.LP1pHP1pControls", 49);
    return c;
}

void modules::filter::LP1pHP1pControls::clinit()
{
    super::clinit();
    static bool in_cl_init = false;
struct clinit_ {
    clinit_() {
        in_cl_init = true;
        LP_LAW_ = new ctoot::control::LogLaw(1.0f, 16.0f, u"");
        HP_LAW_ = new ctoot::control::LogLaw(0.25f, 4.0f, u"");
    }
};

    if(!in_cl_init) {
        static clinit_ clinit_instance;
    }
}

java::lang::Class* ctoot::synth::modules::filter::LP1pHP1pControls::getClass0()
{
    return class_();
}

