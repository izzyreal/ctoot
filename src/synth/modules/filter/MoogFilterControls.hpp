// Generated from /toot2/src/uk/org/toot/synth/modules/filter/MoogFilterControls.java

#pragma once

#include <fwd-toot2.hpp>
#include <java/lang/fwd-toot2.hpp>
#include <synth/modules/filter/fwd-toot2.hpp>
#include <synth/modules/filter/FilterControls.hpp>

struct default_init_tag;

namespace ctoot { namespace synth {modules::filter::MoogFilterControls
    : public FilterControls
{

public:
    typedef FilterControls super;
protected:
    void ctor(int32_t instanceIndex, std::string name, int32_t idOffset);

protected:
    float deriveResonance() override;

    // Generated

public:
    MoogFilterControls(int32_t instanceIndex, std::string name, int32_t idOffset);
protected:
    MoogFilterControls(const ::default_init_tag&);


public:
    static ::java::lang::Class *class_();

private:
    virtual ::java::lang::Class* getClass0();
};
