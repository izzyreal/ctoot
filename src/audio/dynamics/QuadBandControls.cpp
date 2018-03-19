// Generated from /toot2/src/uk/org/toot/audio/dynamics/MultiBandCompressor.java
#include <audio/dynamics/MultiBandCompressor_QuadBandControls.hpp>

#include <java/lang/String.hpp>
#include <audio/dynamics/CompressorControls.hpp>
#include <audio/dynamics/CrossoverControl.hpp>
#include <misc/Localisation.hpp>

uk::org::toot::audio::dynamics::MultiBandCompressor_QuadBandControls::MultiBandCompressor_QuadBandControls(const ::default_init_tag&)
    : super(*static_cast< ::default_init_tag* >(0))
{
    clinit();
}

uk::org::toot::audio::dynamics::MultiBandCompressor_QuadBandControls::MultiBandCompressor_QuadBandControls() 
    : MultiBandCompressor_QuadBandControls(*static_cast< ::default_init_tag* >(0))
{
    ctor();
}

void MultiBandCompressor_QuadBandControls::ctor()
{
    super::ctor(::uk::org::toot::misc::Localisation::getString(u"Quad.Band.Compressor"_j));
    add(new CompressorControls(::uk::org::toot::misc::Localisation::getString(u"Low"_j), int32_t(0)));
    add(new CrossoverControl(::uk::org::toot::misc::Localisation::getString(u"Low"_j), 250.0f));
    add(new CompressorControls(::uk::org::toot::misc::Localisation::getString(u"Lo.Mid"_j), int32_t(10)));
    add(new CrossoverControl(::uk::org::toot::misc::Localisation::getString(u"Mid"_j), 1000.0f));
    add(new CompressorControls(::uk::org::toot::misc::Localisation::getString(u"Hi.Mid"_j), int32_t(20)));
    add(new CrossoverControl(::uk::org::toot::misc::Localisation::getString(u"High"_j), 4000.0f));
    add(new CompressorControls(::uk::org::toot::misc::Localisation::getString(u"High"_j), int32_t(30)));
}

extern java::lang::Class *class_(const char16_t *c, int n);

java::lang::Class* uk::org::toot::audio::dynamics::MultiBandCompressor_QuadBandControls::class_()
{
    static ::java::lang::Class* c = ::class_(u"uk.org.toot.audio.dynamics.MultiBandCompressor.QuadBandControls", 63);
    return c;
}

java::lang::Class* uk::org::toot::audio::dynamics::MultiBandCompressor_QuadBandControls::getClass0()
{
    return class_();
}

