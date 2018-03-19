// Generated from /toot2/src/uk/org/toot/audio/dynamics/VariMuCompressor.java
#include <audio/dynamics/VariMuCompressorControls.hpp>

#include <java/lang/String.hpp>
#include <audio/dynamics/DynamicsIds.hpp>
#include <control/ControlLaw.hpp>
#include <control/LogLaw.hpp>
#include <misc/Localisation.hpp>

uk::org::toot::audio::dynamics::VariMuCompressorControls::VariMuCompressorControls(const ::default_init_tag&)
    : super(*static_cast< ::default_init_tag* >(0))
{
    clinit();
}

uk::org::toot::audio::dynamics::VariMuCompressorControls::VariMuCompressorControls() 
    : VariMuCompressorControls(*static_cast< ::default_init_tag* >(0))
{
    ctor();
}

uk::org::toot::audio::dynamics::VariMuCompressorControls::VariMuCompressorControls(std::string name, int32_t idOffset) 
    : VariMuCompressorControls(*static_cast< ::default_init_tag* >(0))
{
    ctor(name,idOffset);
}

uk::org::toot::control::ControlLaw*& uk::org::toot::audio::dynamics::VariMuCompressorControls::RELEASE_LAW()
{
    clinit();
    return RELEASE_LAW_;
}
uk::org::toot::control::ControlLaw* uk::org::toot::audio::dynamics::VariMuCompressorControls::RELEASE_LAW_;

void VariMuCompressorControls::ctor()
{
    super::ctor(DynamicsIds::VARI_MU_COMPRESSOR, ::uk::org::toot::misc::Localisation::getString(u"Vari.Mu.Comp"_j));
}

void VariMuCompressorControls::ctor(std::string name, int32_t idOffset)
{
    super::ctor(DynamicsIds::VARI_MU_COMPRESSOR, name, idOffset);
}

uk::org::toot::control::ControlLaw* uk::org::toot::audio::dynamics::VariMuCompressorControls::getReleaseLaw()
{
    return RELEASE_LAW_;
}

bool uk::org::toot::audio::dynamics::VariMuCompressorControls::hasGainReductionIndicator()
{
    return true;
}

bool uk::org::toot::audio::dynamics::VariMuCompressorControls::hasDryGain()
{
    return true;
}

bool uk::org::toot::audio::dynamics::VariMuCompressorControls::hasGain()
{
    return true;
}

bool uk::org::toot::audio::dynamics::VariMuCompressorControls::isRMS()
{
    return false;
}

extern java::lang::Class *class_(const char16_t *c, int n);

java::lang::Class* uk::org::toot::audio::dynamics::VariMuCompressorControls::class_()
{
    static ::java::lang::Class* c = ::class_(u"uk.org.toot.audio.dynamics.VariMuCompressor.Controls", 52);
    return c;
}

void VariMuCompressorControls::clinit()
{
    super::clinit();
    static bool in_cl_init = false;
struct clinit_ {
    clinit_() {
        in_cl_init = true;
        RELEASE_LAW_ = new ctoot::control::LogLaw(30.0f, 3000.0f, u"ms"_j);
    }
};

    if(!in_cl_init) {
        static clinit_ clinit_instance;
    }
}

java::lang::Class* uk::org::toot::audio::dynamics::VariMuCompressorControls::getClass0()
{
    return class_();
}

