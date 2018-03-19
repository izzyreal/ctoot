// Generated from /toot2/src/uk/org/toot/audio/basic/tap/TapProcess.java

#pragma once

#include <fwd-toot2.hpp>
#include <audio/basic/tap/fwd-toot2.hpp>
#include <audio/core/fwd-toot2.hpp>
#include <java/lang/Object.hpp>
#include <audio/core/AudioProcess.hpp>

struct default_init_tag;

class uk::org::toot::audio::basic::tap::TapProcess
    : public virtual ::java::lang::Object
    , public virtual ::uk::org::toot::audio::core::AudioProcess
{

public:
    typedef ::java::lang::Object super;

private:
    TapControls* controls {  };
    ::ctoot::audio::core::AudioBuffer* tap {  };
protected:
    void ctor(TapControls* controls);

public:
    void open() /* throws(Exception) */ override;
    int32_t processAudio(::ctoot::audio::core::AudioBuffer* buffer) override;
    void close() /* throws(Exception) */ override;

    // Generated
    TapProcess(TapControls* controls);
protected:
    TapProcess(const ::default_init_tag&);


public:
    static ::java::lang::Class *class_();

private:
    virtual ::java::lang::Class* getClass0();
};
