// Generated from /toot2/src/uk/org/toot/synth/modules/filter/MoogFilter2.java

#pragma once

#include <fwd-toot2.hpp>
#include <synth/modules/filter/fwd-toot2.hpp>
#include <synth/modules/filter/AbstractSynthFilter.hpp>

struct default_init_tag;

namespace ctoot { namespace synth {modules::filter::MoogFilter2
    : public AbstractFilter
{

public:
    typedef AbstractFilter super;

private:
    MoogFilterElement* element {  };
    float res {  };
protected:
    void ctor(FilterVariables* variables);

public:
    virtual float update();
    virtual float filter(float sample, float f);

    // Generated
    MoogFilter2(FilterVariables* variables);
protected:
    MoogFilter2(const ::default_init_tag&);


public:
    static ::java::lang::Class *class_();

private:
    virtual ::java::lang::Class* getClass0();
};
