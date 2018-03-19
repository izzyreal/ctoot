// Generated from /toot2/src/uk/org/toot/audio/basic/tap/TapProcess.java
#include <audio/basic/tap/TapProcess.hpp>

#include <java/lang/NullPointerException.hpp>
#include <java/lang/System.hpp>
#include <audio/basic/tap/TapControls.hpp>
#include <audio/core/AudioBuffer.hpp>
#include <Array.hpp>

template<typename T>
static T* npc(T* t)
{
    if(!t) throw new ::java::lang::NullPointerException();
    return t;
}

uk::org::toot::audio::basic::tap::TapProcess::TapProcess(const ::default_init_tag&)
    : super(*static_cast< ::default_init_tag* >(0))
{
    clinit();
}

uk::org::toot::audio::basic::tap::TapProcess::TapProcess(TapControls* controls) 
    : TapProcess(*static_cast< ::default_init_tag* >(0))
{
    ctor(controls);
}

void uk::org::toot::audio::basic::tap::TapProcess::ctor(TapControls* controls)
{
    super::ctor();
    this->controls = controls;
}

void uk::org::toot::audio::basic::tap::TapProcess::open() /* throws(Exception) */
{
    tap = npc(controls)->getBuffer();
}

int32_t uk::org::toot::audio::basic::tap::TapProcess::processAudio(::ctoot::audio::core::AudioBuffer* buffer)
{
    if(npc(controls)->isInactive())
        return AUDIO_OK;

    npc(tap)->setChannelFormat(buffer->getChannelFormat());
    auto ns = buffer->getSampleCount();
    auto nc = buffer->getChannelCount();
    for (auto i = int32_t(0); i < nc; i++) {
        ::java::lang::System::arraycopy(buffer->getChannel(i), 0, npc(tap)->getChannel(i), 0, ns);
    }
    return AUDIO_OK;
}

void uk::org::toot::audio::basic::tap::TapProcess::close() /* throws(Exception) */
{
    npc(controls)->removeBuffer();
}

extern java::lang::Class *class_(const char16_t *c, int n);

java::lang::Class* uk::org::toot::audio::basic::tap::TapProcess::class_()
{
    static ::java::lang::Class* c = ::class_(u"uk.org.toot.audio.basic.tap.TapProcess", 38);
    return c;
}

java::lang::Class* uk::org::toot::audio::basic::tap::TapProcess::getClass0()
{
    return class_();
}

