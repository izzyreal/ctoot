// Generated from /toot2/src/uk/org/toot/synth/modules/filter/LP1pFilter.java

#pragma once

#include <fwd-toot2.hpp>
#include <synth/modules/filter/fwd-toot2.hpp>
#include <java/lang/Object.hpp>

struct default_init_tag;

namespace ctoot { namespace synth {modules::filter::LP1pFilter
    : public virtual ::java::lang::Object
{

public:
    typedef ::java::lang::Object super;

private:
    float y1 {  };
    float g {  };
protected:
    void ctor(float freq, int32_t rate);

public:
    virtual float filter(float sample);

    // Generated
    LP1pFilter(float freq, int32_t rate);
protected:
    LP1pFilter(const ::default_init_tag&);


public:
    static ::java::lang::Class *class_();

private:
    void init();
    virtual ::java::lang::Class* getClass0();
};
