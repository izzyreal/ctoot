// Generated from /toot2/src/uk/org/toot/audio/basic/BasicServiceProvider.java

#pragma once

#include <audio/basic/fwd-toot2.hpp>
#include <audio/core/fwd-toot2.hpp>
#include <audio/spi/TootAudioServiceProvider.hpp>

struct default_init_tag;

class uk::org::toot::audio::basic::BasicServiceProvider
    : public ::uk::org::toot::audio::spi::TootAudioServiceProvider
{

public:
    typedef ::uk::org::toot::audio::spi::TootAudioServiceProvider super;
protected:
    void ctor();

public:
    ::uk::org::toot::audio::core::AudioProcess* createProcessor(::uk::org::toot::audio::core::AudioControls* c) override;

    // Generated
    BasicServiceProvider();
protected:
    BasicServiceProvider(const ::default_init_tag&);


public:
    static ::java::lang::Class *class_();

private:
    virtual ::java::lang::Class* getClass0();
};
