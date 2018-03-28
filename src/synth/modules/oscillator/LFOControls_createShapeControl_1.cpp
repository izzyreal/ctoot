// Generated from /toot2/src/uk/org/toot/synth/modules/oscillator/LFOControls.java
#include <synth/modules/oscillator/LFOControls_createShapeControl_1.hpp>

#include <java/util/List.hpp>
#include <synth/modules/oscillator/LFOControls.hpp>

 ctoot::synth::modules::oscillator::LFOControls_createShapeControl_1::LFOControls_createShapeControl_1(LFOControls *LFOControls_this, ::java::util::List* shapeNames, int32_t id, std::string name, ::java::lang::Object* value)
    : super(*static_cast< ::default_init_tag* >(0))
    , LFOControls_this(LFOControls_this)
    , shapeNames(shapeNames)
{
    clinit();
    ctor(id, name, value);
}

java::util::List* ctoot::synth::modules::oscillator::LFOControls_createShapeControl_1::getValues()
{
    return shapeNames;
}

extern java::lang::Class *class_(const char16_t *c, int n);

java::lang::Class* ctoot::synth::modules::oscillator::LFOControls_createShapeControl_1::class_()
{
    static ::java::lang::Class* c = ::class_("", 0);
    return c;
}

java::lang::Class* ctoot::synth::modules::oscillator::LFOControls_createShapeControl_1::getClass0()
{
    return class_();
}

