#include <synth/SynthServices.hpp>

#include <synth/MidiSynth.hpp>
#include <synth/SynthControls.hpp>

using namespace ctoot::synth;
using namespace std;

SynthServices::SynthServices()
	: ctoot::service::Services()
{
}
vector<weak_ptr<ctoot::synth::spi::SynthServiceProvider>> SynthServices::providers;

shared_ptr<ctoot::synth::SynthControls> SynthServices::createControls(string name)
{
	shared_ptr<SynthControls> controls;
	for (auto& p : providers) {
		controls = p.lock()->createControls(name);
		if (controls) {
			return controls;
		}
	}
	return {};
}

shared_ptr<ctoot::synth::MidiSynth> SynthServices::createSynth(weak_ptr<SynthControls> controls)
{
	shared_ptr<MidiSynth> synth;
	for (auto& p : providers) {
		synth = p.lock()->createSynth(controls);
		if (synth)
			return synth;
	}
	return {};
}

void SynthServices::scan()
{
	auto prov = lookup(ctoot::synth::spi::SynthServiceProvider());
	providers.clear();
	for (auto& p : prov) {
		auto candidate = dynamic_pointer_cast<ctoot::synth::spi::SynthServiceProvider>(p.lock());
		if (candidate) {
			providers.push_back(candidate);
		}
	}
}

void SynthServices::accept(weak_ptr<ctoot::service::ServiceVisitor> v, string typeIdName)
{
	for (auto& p : providers) {
		p.lock()->accept(v, typeIdName);
	}
}

