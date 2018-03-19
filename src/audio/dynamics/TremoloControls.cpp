// Generated from /toot2/src/uk/org/toot/audio/dynamics/TremoloControls.java
#include <audio/dynamics/TremoloControls.hpp>

#include <java/awt/Color.hpp>
#include <java/lang/NullPointerException.hpp>
#include <java/lang/String.hpp>
#include <audio/dynamics/DynamicsIds.hpp>
#include <control/CompoundControl_ControlColumn.hpp>
#include <control/Control.hpp>
#include <control/FloatControl.hpp>
#include <control/LinearLaw.hpp>
#include <control/LogLaw.hpp>
#include <misc/Localisation.hpp>

template<typename T>
static T* npc(T* t)
{
    if(!t) throw new ::java::lang::NullPointerException();
    return t;
}

uk::org::toot::audio::dynamics::TremoloControls::TremoloControls(const ::default_init_tag&)
    : super(*static_cast< ::default_init_tag* >(0))
{
    clinit();
}

uk::org::toot::audio::dynamics::TremoloControls::TremoloControls() 
    : TremoloControls(*static_cast< ::default_init_tag* >(0))
{
    ctor();
}

uk::org::toot::control::ControlLaw*& uk::org::toot::audio::dynamics::TremoloControls::rateLaw()
{
    clinit();
    return rateLaw_;
}
uk::org::toot::control::ControlLaw* uk::org::toot::audio::dynamics::TremoloControls::rateLaw_;

constexpr int32_t uk::org::toot::audio::dynamics::TremoloControls::RATE_ID;

constexpr int32_t uk::org::toot::audio::dynamics::TremoloControls::DEPTH_ID;

void TremoloControls::ctor()
{
    super::ctor(DynamicsIds::TREMOLO_ID, ::uk::org::toot::misc::Localisation::getString(u"Tremolo"_j));
    auto cc = new ctoot::control::CompoundControl_ControlColumn();
    npc(cc)->add(static_cast< ctoot::control::Control* >(rateControl = createRateControl()));
    npc(cc)->add(static_cast< ctoot::control::Control* >(depthControl = createDepthControl()));
    add(cc);
}

uk::org::toot::control::FloatControl* uk::org::toot::audio::dynamics::TremoloControls::createRateControl()
{
    return new ctoot::control::FloatControl(RATE_ID, ::uk::org::toot::misc::Localisation::getString(u"Rate"_j), rateLaw_, 0.01f, 3.5f);
}

uk::org::toot::control::FloatControl* uk::org::toot::audio::dynamics::TremoloControls::createDepthControl()
{
    auto c = new ctoot::control::FloatControl(DEPTH_ID, ::uk::org::toot::misc::Localisation::getString(u"Depth"_j), ctoot::control::LinearLaw::UNITY(), 0.01f, 0.25f);
    npc(c)->setInsertColor(::java::awt::Color::LIGHT_GRAY());
    return c;
}

float TremoloControls::getDepth()
{
    return npc(depthControl)->getValue();
}

float TremoloControls::getRate()
{
    return npc(rateControl)->getValue();
}

extern java::lang::Class *class_(const char16_t *c, int n);

java::lang::Class* uk::org::toot::audio::dynamics::TremoloControls::class_()
{
    static ::java::lang::Class* c = ::class_(u"uk.org.toot.audio.dynamics.TremoloControls", 42);
    return c;
}

void TremoloControls::clinit()
{
    super::clinit();
    static bool in_cl_init = false;
struct clinit_ {
    clinit_() {
        in_cl_init = true;
        rateLaw_ = new ctoot::control::LogLaw(0.5f, 10.0f, u"Hz"_j);
    }
};

    if(!in_cl_init) {
        static clinit_ clinit_instance;
    }
}

bool uk::org::toot::audio::dynamics::TremoloControls::isBypassed()
{
    return AudioControls::isBypassed();
}

java::lang::Class* uk::org::toot::audio::dynamics::TremoloControls::getClass0()
{
    return class_();
}

