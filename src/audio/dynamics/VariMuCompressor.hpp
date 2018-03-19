// Generated from /toot2/src/uk/org/toot/audio/dynamics/VariMuCompressor.java

#pragma once

#include <fwd-toot2.hpp>
#include <audio/dynamics/fwd-toot2.hpp>
#include <audio/dynamics/ClassicDynamicsProcess.hpp>

struct default_init_tag;

class VariMuCompressor
    : public ClassicDynamicsProcess
{

public:
    typedef ClassicDynamicsProcess super;
protected:
    void ctor(DynamicsVariables* vars);

public: /* protected */
    float function(float value) override;

private:
    static ::floatArray* table_;

    // Generated

public:
    VariMuCompressor(DynamicsVariables* vars);
protected:
    VariMuCompressor(const ::default_init_tag&);


public:
    static ::java::lang::Class *class_();
    static void clinit();

private:
    static ::floatArray*& table();
    virtual ::java::lang::Class* getClass0();
    friend class VariMuCompressorControls;
};
