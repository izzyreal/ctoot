// Generated from /toot2/src/uk/org/toot/synth/modules/filter/HP1pFilter.java

#pragma once

#include <fwd-toot2.hpp>
#include <synth/modules/filter/fwd-toot2.hpp>
#include <synth/modules/filter/LP1pFilter.hpp>

struct default_init_tag;

namespace ctoot { namespace synth {modules::filter::HP1pFilter
    : public LP1pFilter
{

public:
    typedef LP1pFilter super;
protected:
    void ctor(float freq, int32_t rate);

public:
    float filter(float sample) override;

    // Generated
    HP1pFilter(float freq, int32_t rate);
protected:
    HP1pFilter(const ::default_init_tag&);


public:
    static ::java::lang::Class *class_();

private:
    virtual ::java::lang::Class* getClass0();
};
