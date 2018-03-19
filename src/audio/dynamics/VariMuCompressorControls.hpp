// Generated from /toot2/src/uk/org/toot/audio/dynamics/VariMuCompressor.java

#pragma once

#include <fwd-toot2.hpp>
#include <java/lang/fwd-toot2.hpp>
#include <audio/dynamics/fwd-toot2.hpp>
#include <control/fwd-toot2.hpp>
#include <audio/dynamics/DynamicsControls.hpp>

struct default_init_tag;

class VariMuCompressorControls
    : public DynamicsControls
{

public:
    typedef DynamicsControls super;

private:
    static ctoot::control::ControlLaw* RELEASE_LAW_;
protected:
    void ctor();
    void ctor(std::string name, int32_t idOffset);

public: /* protected */
    ctoot::control::ControlLaw* getReleaseLaw() override;
    bool hasGainReductionIndicator() override;
    bool hasDryGain() override;
    bool hasGain() override;

public:
    bool isRMS() override;

    // Generated
    VariMuCompressorControls();
    VariMuCompressorControls(std::string name, int32_t idOffset);
protected:
    VariMuCompressorControls(const ::default_init_tag&);


public:
    static ::java::lang::Class *class_();
    static void clinit();

private:
    static ctoot::control::ControlLaw*& RELEASE_LAW();
    virtual ::java::lang::Class* getClass0();
    friend class VariMuCompressor;
};
