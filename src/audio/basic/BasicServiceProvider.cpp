// Generated from /toot2/src/uk/org/toot/audio/basic/BasicServiceProvider.java
#include <audio/basic/BasicServiceProvider.hpp>

#include <java/lang/Class.hpp>
#include <java/lang/ClassCastException.hpp>
#include <java/lang/String.hpp>
#include <audio/basic/BasicIds.hpp>
#include <audio/basic/stereoImage/StereoImageControls.hpp>
#include <audio/basic/stereoImage/StereoImageProcess.hpp>
#include <audio/basic/stereoImage/StereoImageProcessVariables.hpp>
#include <audio/basic/tap/TapControls.hpp>
#include <audio/basic/tap/TapProcess.hpp>
#include <audio/basic/trim/TrimControls.hpp>
#include <audio/basic/trim/TrimProcess.hpp>
#include <audio/core/AudioControls.hpp>
#include <audio/core/ChannelFormat.hpp>
#include <misc/Localisation.hpp>

template<typename T, typename U>
static T java_cast(U* u)
{
    if(!u) return static_cast<T>(nullptr);
    auto t = dynamic_cast<T>(u);
    if(!t) throw new ::java::lang::ClassCastException();
    return t;
}

uk::org::toot::audio::basic::BasicServiceProvider::BasicServiceProvider(const ::default_init_tag&)
    : super(*static_cast< ::default_init_tag* >(0))
{
    clinit();
}

uk::org::toot::audio::basic::BasicServiceProvider::BasicServiceProvider() 
    : BasicServiceProvider(*static_cast< ::default_init_tag* >(0))
{
    ctor();
}

void uk::org::toot::audio::basic::BasicServiceProvider::ctor()
{
    super::ctor(::uk::org::toot::misc::Localisation::getString(u"Basic"_j), u"0.1"_j);
    auto family = ::uk::org::toot::misc::Localisation::getString(u"Basic"_j);
    addControls(::uk::org::toot::audio::basic::tap::TapControls::class_(), BasicIds::TAP, ::uk::org::toot::misc::Localisation::getString(u"Tap"_j), family, u"0.1"_j);
    addControls(::uk::org::toot::audio::basic::trim::TrimControls::class_(), BasicIds::TRIM, ::uk::org::toot::misc::Localisation::getString(u"Trim"_j), family, u"0.1"_j);
    addControls(::uk::org::toot::audio::basic::stereoImage::StereoImageControls::class_(), BasicIds::STEREO_IMAGE, ::uk::org::toot::misc::Localisation::getString(u"Stereo.Image"_j), family, u"0.1"_j, ::uk::org::toot::audio::core::ChannelFormat::STEREO(), nullptr);
    add(::uk::org::toot::audio::basic::tap::TapProcess::class_(), ::uk::org::toot::misc::Localisation::getString(u"Tap"_j), family, u"0.1"_j);
    add(::uk::org::toot::audio::basic::trim::TrimProcess::class_(), ::uk::org::toot::misc::Localisation::getString(u"Trim"_j), family, u"0.1"_j);
    add(::uk::org::toot::audio::basic::stereoImage::StereoImageProcess::class_(), ::uk::org::toot::misc::Localisation::getString(u"Stereo.Image"_j), family, u"0.1"_j);
}

uk::org::toot::audio::core::AudioProcess* uk::org::toot::audio::basic::BasicServiceProvider::createProcessor(::uk::org::toot::audio::core::AudioControls* c)
{
    if(dynamic_cast< ::uk::org::toot::audio::basic::tap::TapControls* >(c) != nullptr) {
        return new ::uk::org::toot::audio::basic::tap::TapProcess(java_cast< ::uk::org::toot::audio::basic::tap::TapControls* >(c));
    } else if(dynamic_cast< ::uk::org::toot::audio::basic::trim::TrimControls* >(c) != nullptr) {
        return new ::uk::org::toot::audio::basic::trim::TrimProcess(java_cast< ::uk::org::toot::audio::basic::trim::TrimControls* >(c));
    } else if(dynamic_cast< ::uk::org::toot::audio::basic::stereoImage::StereoImageProcessVariables* >(c) != nullptr) {
        return new ::uk::org::toot::audio::basic::stereoImage::StereoImageProcess(java_cast< ::uk::org::toot::audio::basic::stereoImage::StereoImageProcessVariables* >(c));
    }
    return nullptr;
}

extern java::lang::Class *class_(const char16_t *c, int n);

java::lang::Class* uk::org::toot::audio::basic::BasicServiceProvider::class_()
{
    static ::java::lang::Class* c = ::class_(u"uk.org.toot.audio.basic.BasicServiceProvider", 44);
    return c;
}

java::lang::Class* uk::org::toot::audio::basic::BasicServiceProvider::getClass0()
{
    return class_();
}

