#include <synth/channels/AllTootSynthChannelsServiceProvider.hpp>

#include <synth/SynthChannelControls.hpp>
//#include <synth/channels/copal/CopalSynthChannel.hpp>
//#include <synth/channels/copal/CopalSynthControls.hpp>
//#include <synth/channels/nine/NineSynthChannel.hpp>
//#include <synth/channels/nine/NineSynthControls.hpp>
//#include <synth/channels/pluck/PluckSynthChannel.hpp>
//#include <synth/channels/pluck/PluckSynthControls.hpp>
//#include <synth/channels/total/TotalSynthChannel.hpp>
//#include <synth/channels/total/TotalSynthControls.hpp>
#include <synth/channels/valor/ValorSynthChannel.hpp>
#include <synth/channels/valor/ValorSynthControls.hpp>
//#include <synth/channels/whirl/WhirlSynthChannel.hpp>
//#include <synth/channels/whirl/WhirlSynthControls.hpp>
#include <synth/id/TootSynthControlsId.hpp>

using namespace ctoot::synth::channels;

AllTootSynthChannelsServiceProvider::AllTootSynthChannelsServiceProvider()
	: ctoot::synth::spi::TootSynthChannelServiceProvider("Toot Synth Channels", "0.2")
{
	std::string name;
    name = ctoot::synth::channels::valor::ValorSynthControls::NAME();
    addControls(ctoot::synth::channels::valor::ValorSynthControls::class_(), ctoot::synth::id::TootSynthControlsId::VALOR_CHANNEL_ID, name, u"Virtual Analog Polyphonic", u"0.2");
    add(ctoot::synth::channels::valor::ValorSynthChannel::class_(), name, u"Valor", u"0.2");
    name = ctoot::synth::channels::pluck::PluckSynthControls::NAME();
    addControls(ctoot::synth::channels::pluck::PluckSynthControls::class_(), ctoot::synth::id::TootSynthControlsId::PLUCK_CHANNEL_ID, name, u"Physically Modelled Plucked String", u"0.1");
    add(ctoot::synth::channels::pluck::PluckSynthChannel::class_(), name, u"Pluck", u"0.1");
    name = ctoot::synth::channels::copal::CopalSynthControls::NAME();
    addControls(ctoot::synth::channels::copal::CopalSynthControls::class_(), ctoot::synth::id::TootSynthControlsId::COPAL_CHANNEL_ID, name, u"Paraphonic Sring Ensemble", u"0.2");
    add(ctoot::synth::channels::copal::CopalSynthChannel::class_(), name, u"Cepal", u"0.2");
    name = ctoot::synth::channels::whirl::WhirlSynthControls::NAME();
    addControls(ctoot::synth::channels::whirl::WhirlSynthControls::class_(), ctoot::synth::id::TootSynthControlsId::WHIRL_CHANNEL_ID, name, u"Virtual Analog Monophonic", u"0.2");
    add(ctoot::synth::channels::whirl::WhirlSynthChannel::class_(), name, u"Whirl", u"0.2");
    name = ctoot::synth::channels::total::TotalSynthControls::NAME();
    addControls(ctoot::synth::channels::total::TotalSynthControls::class_(), ctoot::synth::id::TootSynthControlsId::TOTAL_CHANNEL_ID, name, u"Digital Polyphonic", u"0.1");
    add(ctoot::synth::channels::total::TotalSynthChannel::class_(), name, u"Total", u"0.1");
    name = ctoot::synth::channels::nine::NineSynthControls::NAME();
    addControls(ctoot::synth::channels::nine::NineSynthControls::class_(), ctoot::synth::id::TootSynthControlsId::NINE_CHANNEL_ID, name, u"Hammond Drawbar Organ", u"0.1");
    add(ctoot::synth::channels::nine::NineSynthChannel::class_(), name, u"Nine", u"0.1");
}

 ctoot::synth::SynthChannel* ctoot::synth::channels::AllTootSynthChannelsServiceProvider::createSynthChannel(ctoot::synth::SynthChannelControls* c)
{
    if(dynamic_cast< ctoot::synth::channels::valor::ValorSynthControls* >(c) != nullptr) {
        return new ctoot::synth::channels::valor::ValorSynthChannel(java_cast< ctoot::synth::channels::valor::ValorSynthControls* >(c));
    } else if(dynamic_cast< ctoot::synth::channels::pluck::PluckSynthControls* >(c) != nullptr) {
        return new ctoot::synth::channels::pluck::PluckSynthChannel(java_cast< ctoot::synth::channels::pluck::PluckSynthControls* >(c));
    } else if(dynamic_cast< ctoot::synth::channels::copal::CopalSynthControls* >(c) != nullptr) {
        return new ctoot::synth::channels::copal::CopalSynthChannel(java_cast< ctoot::synth::channels::copal::CopalSynthControls* >(c));
    } else if(dynamic_cast< ctoot::synth::channels::whirl::WhirlSynthControls* >(c) != nullptr) {
        return new ctoot::synth::channels::whirl::WhirlSynthChannel(java_cast< ctoot::synth::channels::whirl::WhirlSynthControls* >(c));
    } else if(dynamic_cast< ctoot::synth::channels::total::TotalSynthControls* >(c) != nullptr) {
        return new ctoot::synth::channels::total::TotalSynthChannel(java_cast< ctoot::synth::channels::total::TotalSynthControls* >(c));
    } else if(dynamic_cast< ctoot::synth::channels::nine::NineSynthControls* >(c) != nullptr) {
        return new ctoot::synth::channels::nine::NineSynthChannel(java_cast< ctoot::synth::channels::nine::NineSynthControls* >(c));
    }
    return nullptr;
}

extern java::lang::Class *class_(const char16_t *c, int n);

java::lang::Class* ctoot::synth::channels::AllTootSynthChannelsServiceProvider::class_()
{
    static ::java::lang::Class* c = ::class_("uk.org.toot.synth.channels.AllTootSynthChannelsServiceProvider", 62);
    return c;
}

java::lang::Class* ctoot::synth::channels::AllTootSynthChannelsServiceProvider::getClass0()
{
    return class_();
}

