#include <synth/synths/multi/MultiSynthServiceProvider.hpp>

#include <control/id/ProviderId.hpp>
#include <synth/SynthControls.hpp>
#include <synth/synths/multi/MultiMidiSynth.hpp>
#include <synth/synths/multi/MultiSynthControls.hpp>
#include <mpc/MpcMultiMidiSynth.hpp>
#include <mpc/MpcMultiSynthControls.hpp>

using namespace ctoot::synth::synths::multi;
using namespace std;

MultiSynthServiceProvider::MultiSynthServiceProvider()
	: ctoot::synth::spi::SynthServiceProvider(ctoot::control::id::ProviderId::TOOT_PROVIDER_ID, "Toot Software", MultiSynthControls::NAME(), "0.1")
{
    auto name = MultiSynthControls::NAME();
    addControls("ctoot::synth::synths::multi::MultiSynthControls", MultiSynthControls::ID, name, "", "0.1");
    //add(MultiMidiSynth::class_(), name, "", "0.1");
}

shared_ptr<ctoot::synth::MidiSynth> MultiSynthServiceProvider::createSynth(weak_ptr<ctoot::synth::SynthControls> c)
{
	if (dynamic_pointer_cast<ctoot::mpc::MpcMultiSynthControls>(c.lock())) {
		return make_shared<ctoot::mpc::MpcMultiMidiSynth>(dynamic_pointer_cast<MultiSynthControls>(c.lock()));
	}
	if (dynamic_pointer_cast<MultiSynthControls>(c.lock())) {
        return make_shared<MultiMidiSynth>(dynamic_pointer_cast<MultiSynthControls>(c.lock()));
    }
	return {};
}
