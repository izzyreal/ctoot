// Generated from /toot2/src/uk/org/toot/synth/modules/envelope/EnvelopeGenerator.java
#include <synth/modules/envelope/EnvelopeGenerator_State.hpp>

#include <java/io/Serializable.hpp>
#include <java/lang/ArrayStoreException.hpp>
#include <java/lang/Comparable.hpp>
#include <java/lang/Enum.hpp>
#include <java/lang/IllegalArgumentException.hpp>
#include <java/lang/String.hpp>
#include <SubArray.hpp>
#include <ObjectArray.hpp>

template<typename ComponentType, typename... Bases> struct SubArray;
namespace java
{
    namespace io
    {
typedef ::SubArray< ::java::io::Serializable, ::java::lang::ObjectArray > SerializableArray;
    } // io

    namespace lang
    {
typedef ::SubArray< ::java::lang::Comparable, ObjectArray > ComparableArray;
typedef ::SubArray< ::java::lang::Enum, ObjectArray, ComparableArray, ::java::io::SerializableArray > EnumArray;
    } // lang
} // java

namespace uk
{
    namespace org
    {
        namespace toot
        {
            namespace synth
            {
                namespace modules
                {
                    namespace envelope
                    {
typedef ::SubArray< ctoot::synth::modules::envelope::EnvelopeGenerator_State, ::java::lang::EnumArray > EnvelopeGenerator_StateArray;
                    } // envelope
                } // modules
            } // synth
        } // toot
    } // org
} // uk

 ctoot::synth::modules::envelope::EnvelopeGenerator_State::EnvelopeGenerator_State(const ::default_init_tag&)
    : super(*static_cast< ::default_init_tag* >(0))
{
    clinit();
}

 ctoot::synth::modules::envelope::EnvelopeGenerator_State::EnvelopeGenerator_State(std::string name, int ordinal)
    : EnvelopeGenerator_State(*static_cast< ::default_init_tag* >(0))
{
    ctor(name, ordinal);
}

 ctoot::synth::modules::envelope::EnvelopeGenerator_State* ctoot::synth::modules::envelope::EnvelopeGenerator_State::DELAY = new ctoot::synth::modules::envelope::EnvelopeGenerator_State("DELAY", 0);
 ctoot::synth::modules::envelope::EnvelopeGenerator_State* ctoot::synth::modules::envelope::EnvelopeGenerator_State::ATTACK = new ctoot::synth::modules::envelope::EnvelopeGenerator_State("ATTACK", 1);
 ctoot::synth::modules::envelope::EnvelopeGenerator_State* ctoot::synth::modules::envelope::EnvelopeGenerator_State::HOLD = new ctoot::synth::modules::envelope::EnvelopeGenerator_State("HOLD", 2);
 ctoot::synth::modules::envelope::EnvelopeGenerator_State* ctoot::synth::modules::envelope::EnvelopeGenerator_State::DECAY = new ctoot::synth::modules::envelope::EnvelopeGenerator_State("DECAY", 3);
 ctoot::synth::modules::envelope::EnvelopeGenerator_State* ctoot::synth::modules::envelope::EnvelopeGenerator_State::SUSTAIN = new ctoot::synth::modules::envelope::EnvelopeGenerator_State("SUSTAIN", 4);
 ctoot::synth::modules::envelope::EnvelopeGenerator_State* ctoot::synth::modules::envelope::EnvelopeGenerator_State::RELEASE = new ctoot::synth::modules::envelope::EnvelopeGenerator_State("RELEASE", 5);
 ctoot::synth::modules::envelope::EnvelopeGenerator_State* ctoot::synth::modules::envelope::EnvelopeGenerator_State::COMPLETE = new ctoot::synth::modules::envelope::EnvelopeGenerator_State("COMPLETE", 6);
extern java::lang::Class *class_(const char16_t *c, int n);

java::lang::Class* ctoot::synth::modules::envelope::EnvelopeGenerator_State::class_()
{
    static ::java::lang::Class* c = ::class_("uk.org.toot.synth.modules.envelope.EnvelopeGenerator.State", 58);
    return c;
}

 ctoot::synth::modules::envelope::EnvelopeGenerator_State* ctoot::synth::modules::envelope::EnvelopeGenerator_State::valueOf(std::string a0)
{
    if(ATTACK->toString()->equals(a0))
        return ATTACK;
    if(COMPLETE->toString()->equals(a0))
        return COMPLETE;
    if(DECAY->toString()->equals(a0))
        return DECAY;
    if(DELAY->toString()->equals(a0))
        return DELAY;
    if(HOLD->toString()->equals(a0))
        return HOLD;
    if(RELEASE->toString()->equals(a0))
        return RELEASE;
    if(SUSTAIN->toString()->equals(a0))
        return SUSTAIN;
    throw new ::java::lang::IllegalArgumentException(a0);
}

 ctoot::synth::modules::envelope::EnvelopeGenerator_StateArray* ctoot::synth::modules::envelope::EnvelopeGenerator_State::values()
{
    return new ctoot::synth::modules::envelope::EnvelopeGenerator_StateArray({
        ATTACK,
        COMPLETE,
        DECAY,
        DELAY,
        HOLD,
        RELEASE,
        SUSTAIN,
    });
}

java::lang::Class* ctoot::synth::modules::envelope::EnvelopeGenerator_State::getClass0()
{
    return class_();
}

