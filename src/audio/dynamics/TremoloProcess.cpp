// Generated from /toot2/src/uk/org/toot/audio/dynamics/TremoloProcess.java
#include <audio/dynamics/TremoloProcess.hpp>

#include <java/io/Serializable.hpp>
#include <java/lang/ArrayStoreException.hpp>
#include <java/lang/Cloneable.hpp>
#include <java/lang/Math.hpp>
#include <java/lang/NullPointerException.hpp>
#include <audio/core/AudioBuffer.hpp>
#include <audio/dynamics/TremoloProcess_Variables.hpp>
#include <dsp/FastMath.hpp>
#include <Array.hpp>
#include <SubArray.hpp>
#include <ObjectArray.hpp>

template<typename ComponentType, typename... Bases> struct SubArray;
namespace java
{
    namespace io
    {
typedef ::SubArray< ::java::io::Serializable, ::java::lang::ObjectArray > SerializableArray;
    } // io

    namespace lang
    {
typedef ::SubArray< ::java::lang::Cloneable, ObjectArray > CloneableArray;
    } // lang
} // java

namespace 
{
typedef ::SubArray< ::floatArray, ::java::lang::CloneableArray, ::java::io::SerializableArray > floatArrayArray;
} // 

template<typename T>
static T* npc(T* t)
{
    if(!t) throw new ::java::lang::NullPointerException();
    return t;
}

uk::org::toot::audio::dynamics::TremoloProcess::TremoloProcess(const ::default_init_tag&)
    : super(*static_cast< ::default_init_tag* >(0))
{
    clinit();
}

uk::org::toot::audio::dynamics::TremoloProcess::TremoloProcess(TremoloProcess_Variables* variables) 
    : TremoloProcess(*static_cast< ::default_init_tag* >(0))
{
    ctor(variables);
}

void TremoloProcess::init()
{
    samples = new ::floatArrayArray(int32_t(8));
    lfoPhase = 0.0f;
}

void TremoloProcess::ctor(TremoloProcess_Variables* variables)
{
    super::ctor();
    init();
    vars = variables;
}

int32_t uk::org::toot::audio::dynamics::TremoloProcess::processAudio(ctoot::audio::core::AudioBuffer* buffer)
{
    if(vars->isBypassed())
        return AUDIO_OK;

    auto ns = buffer->getSampleCount();
    auto nc = buffer->getChannelCount();
    for (auto c = int32_t(0); c < nc; c++) {
        samples->set(c, buffer->getChannel(c));
    }
    auto _lfoInc = int32_t(2) * static_cast< float >(::java::lang::Math::PI) * (vars->getRate() / buffer->getSampleRate());
    auto depth = vars->getDepth();
    float mod;
    for (auto s = int32_t(0); s < ns; s++) {
        mod = int32_t(1) - depth * ((ctoot::dsp::FastMath::sin(lfoPhase) + 1.0f) * 0.5f);
        lfoPhase += _lfoInc;
        if(lfoPhase >= ::java::lang::Math::PI)
            lfoPhase -= ::java::lang::Math::PI * int32_t(2);

        for (auto c = int32_t(0); c < nc; c++) {
            (*(*samples)[c])[s] *= mod;
        }
    }
    return AUDIO_OK;
}

extern java::lang::Class *class_(const char16_t *c, int n);

java::lang::Class* uk::org::toot::audio::dynamics::TremoloProcess::class_()
{
    static ::java::lang::Class* c = ::class_(u"uk.org.toot.audio.dynamics.TremoloProcess", 41);
    return c;
}

java::lang::Class* uk::org::toot::audio::dynamics::TremoloProcess::getClass0()
{
    return class_();
}

