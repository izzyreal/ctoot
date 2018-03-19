// Generated from /toot2/src/uk/org/toot/audio/dynamics/TremoloControls.java

#pragma once

#include <fwd-toot2.hpp>
#include <audio/dynamics/fwd-toot2.hpp>
#include <control/fwd-toot2.hpp>
#include <audio/core/AudioControls.hpp>
#include <audio/dynamics/TremoloProcess_Variables.hpp>

struct default_init_tag;

class TremoloControls
    : public ctoot::audio::core::AudioControls
    , public virtual TremoloProcess_Variables
{

public:
    typedef ctoot::audio::core::AudioControls super;

private:
    static ctoot::control::ControlLaw* rateLaw_;

public: /* protected */
    static constexpr int32_t RATE_ID { int32_t(1) };
    static constexpr int32_t DEPTH_ID { int32_t(2) };

private:
    ctoot::control::FloatControl* rateControl {  };
    ctoot::control::FloatControl* depthControl {  };
protected:
    void ctor();

public: /* protected */
    virtual ctoot::control::FloatControl* createRateControl();
    virtual ctoot::control::FloatControl* createDepthControl();

public:
    float getDepth() override;
    float getRate() override;

    // Generated
    TremoloControls();
protected:
    TremoloControls(const ::default_init_tag&);


public:
    static ::java::lang::Class *class_();
    static void clinit();
    virtual bool isBypassed();

public: /* protected */
    static ctoot::control::ControlLaw*& rateLaw();

private:
    virtual ::java::lang::Class* getClass0();
};
