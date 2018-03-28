// Generated from /toot2/src/uk/org/toot/synth/modules/oscillator/LFOControls.java

#pragma once

#include <fwd-toot2.hpp>
#include <java/lang/fwd-toot2.hpp>
#include <java/util/fwd-toot2.hpp>
#include <synth/modules/oscillator/fwd-toot2.hpp>
#include <control/EnumControl.hpp>

struct default_init_tag;

namespace ctoot { namespace synth {modules::oscillator::LFOControls_createShapeControl_1
    : public ctoot::control::EnumControl
{

public:
    typedef ctoot::control::EnumControl super;
    ::java::util::List* getValues() override;

    // Generated
    LFOControls_createShapeControl_1(LFOControls *LFOControls_this, ::java::util::List* shapeNames, int32_t id, std::string name, ::java::lang::Object* value);
    static ::java::lang::Class *class_();
    LFOControls *LFOControls_this;
    ::java::util::List* shapeNames;

private:
    virtual ::java::lang::Class* getClass0();
    friend class LFOControls;
};
