// Generated from /toot2/src/uk/org/toot/audio/dynamics/TremoloProcess.java

#pragma once

#include <fwd-toot2.hpp>
#include <java/io/fwd-toot2.hpp>
#include <java/lang/fwd-toot2.hpp>
#include <audio/core/fwd-toot2.hpp>
#include <audio/dynamics/fwd-toot2.hpp>
#include <audio/core/SimpleAudioProcess.hpp>

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

struct default_init_tag;

class TremoloProcess
    : public ctoot::audio::core::SimpleAudioProcess
{

public:
    typedef ctoot::audio::core::SimpleAudioProcess super;

private:
    TremoloProcess_Variables* vars {  };
    ::floatArrayArray* samples {  };
    float lfoPhase {  };
protected:
    void ctor(TremoloProcess_Variables* variables);

public:
    int32_t processAudio(ctoot::audio::core::AudioBuffer* buffer) override;

    // Generated
    TremoloProcess(TremoloProcess_Variables* variables);
protected:
    TremoloProcess(const ::default_init_tag&);


public:
    static ::java::lang::Class *class_();

private:
    void init();
    virtual ::java::lang::Class* getClass0();
    friend class TremoloProcess_Variables;
};
