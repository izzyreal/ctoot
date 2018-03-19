// Generated from /toot2/src/uk/org/toot/audio/dynamics/MultiBandCompressor.java

#pragma once

#include <audio/dynamics/fwd-toot2.hpp>
#include <audio/dynamics/MultiBandControls.hpp>

struct default_init_tag;

class MultiBandCompressor_QuadBandControls
    : public MultiBandControls
{

public:
    typedef MultiBandControls super;
protected:
    void ctor();

    // Generated

public:
    MultiBandCompressor_QuadBandControls();
protected:
    MultiBandCompressor_QuadBandControls(const ::default_init_tag&);


public:
    static ::java::lang::Class *class_();

private:
    virtual ::java::lang::Class* getClass0();
    friend class MultiBandCompressor;
    friend class MultiBandControls;
    friend class DualBandControls;
};
