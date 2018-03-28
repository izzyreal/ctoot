// Generated from /toot2/src/uk/org/toot/synth/modules/filter/MoogFilterElement.java

#pragma once

#include <fwd-toot2.hpp>
#include <synth/modules/filter/fwd-toot2.hpp>
#include <java/lang/Object.hpp>

struct default_init_tag;

namespace ctoot { namespace synth {modules::filter::MoogFilterElement
    : public virtual ::java::lang::Object
{

public:
    typedef ::java::lang::Object super;

private:
    double in1 {  }, in2 {  }, in3 {  }, in4 {  }, out1 {  }, out2 {  }, out3 {  }, out4 {  };

public:
    virtual float filter(float input, float fc, float res);

    // Generated
    MoogFilterElement();
protected:
    MoogFilterElement(const ::default_init_tag&);


public:
    static ::java::lang::Class *class_();

private:
    virtual ::java::lang::Class* getClass0();
};
