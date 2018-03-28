// Generated from /toot2/src/uk/org/toot/synth/modules/GlideControls.java
#include <synth/modules/GlideControls.hpp>

#include <java/awt/Color.hpp>
#include <java/lang/NullPointerException.hpp>
#include <java/lang/String.hpp>
#include <control/BooleanControl.hpp>
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

 ctoot::synth::modules::GlideControls::GlideControls(const ::default_init_tag&)
    : super(*static_cast< ::default_init_tag* >(0))
{
    clinit();
}

 ctoot::synth::modules::GlideControls::GlideControls(int32_t idOffset) 
    : GlideControls(*static_cast< ::default_init_tag* >(0))
{
    ctor(idOffset);
}

 ctoot::synth::modules::GlideControls::GlideControls(int32_t id, std::string name, int32_t idOffset) 
    : GlideControls(*static_cast< ::default_init_tag* >(0))
{
    ctor(id,name,idOffset);
}

void modules::GlideControls::init()
{
    idOffset = int32_t(0);
}

uk::org::toot::control::ControlLaw*& ctoot::synth::modules::GlideControls::TIME_LAW()
{
    clinit();
    return TIME_LAW_;
}
uk::org::toot::control::ControlLaw* ctoot::synth::modules::GlideControls::TIME_LAW_;

constexpr int32_t ctoot::synth::modules::GlideControls::ENABLE;

constexpr int32_t ctoot::synth::modules::GlideControls::TIME;

void modules::GlideControls::ctor(int32_t idOffset)
{
    ctor(int32_t(112), ctoot::misc::Localisation::getString("Glide"), idOffset);
}

void modules::GlideControls::ctor(int32_t id, std::string name, int32_t idOffset)
{
    super::ctor(id, name);
    init();
    this->idOffset = idOffset;
    createControls();
    deriveSampleRateIndependentVariables();
}

void modules::GlideControls::derive(ctoot::control::Control* c)
{
    switch (c->getId() - idOffset) {
    case ENABLE:
        glideEnable = deriveEnable();
        break;
    case TIME:
        glideMillis = deriveTime();
        break;
    }

}

void modules::GlideControls::createControls()
{
    add(enableControl = createEnableControl());
    add(timeControl = createTimeControl());
}

void modules::GlideControls::deriveSampleRateIndependentVariables()
{
    glideEnable = deriveEnable();
    glideMillis = deriveTime();
}

bool ctoot::synth::modules::GlideControls::deriveEnable()
{
    return npc(enableControl)->getValue();
}

int32_t ctoot::synth::modules::GlideControls::deriveTime()
{
    return static_cast< int32_t >(npc(timeControl)->getValue());
}

uk::org::toot::control::BooleanControl* ctoot::synth::modules::GlideControls::createEnableControl()
{
    auto control = new ctoot::control::BooleanControl(ENABLE + idOffset, u"On", true);
    control->setStateColor(true, ::java::awt::Color::GREEN());
    return control;
}

uk::org::toot::control::FloatControl* ctoot::synth::modules::GlideControls::createTimeControl()
{
    return new ctoot::control::FloatControl(TIME + idOffset, u"Time", TIME_LAW_, 1.0f, 100.0f);
}

int32_t ctoot::synth::modules::GlideControls::getGlideMilliseconds()
{
    return glideMillis;
}

bool ctoot::synth::modules::GlideControls::isGlideEnabled()
{
    return glideEnable;
}

extern java::lang::Class *class_(const char16_t *c, int n);

java::lang::Class* ctoot::synth::modules::GlideControls::class_()
{
    static ::java::lang::Class* c = ::class_("uk.org.toot.synth.modules.GlideControls", 39);
    return c;
}

void modules::GlideControls::clinit()
{
    super::clinit();
    static bool in_cl_init = false;
struct clinit_ {
    clinit_() {
        in_cl_init = true;
        TIME_LAW_ = new ctoot::control::LogLaw(10.0f, 1000.0f, u"ms");
    }
};

    if(!in_cl_init) {
        static clinit_ clinit_instance;
    }
}

java::lang::Class* ctoot::synth::modules::GlideControls::getClass0()
{
    return class_();
}

