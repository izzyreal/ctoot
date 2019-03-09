#include <synth/SynthServices.hpp>

//#include <service/ServicePrinter.hpp>
#include <synth/MidiSynth.hpp>
#include <synth/SynthControls.hpp>

using namespace ctoot::synth;
using namespace std;

SynthServices::SynthServices()
	: ctoot::service::Services()
{
}
vector<weak_ptr<ctoot::synth::spi::SynthServiceProvider>> SynthServices::providers;

string SynthServices::lookupModuleName(int32_t providerId, int32_t moduleId)
{
	for (auto& p : providers) {
		if (p.lock()->getProviderId() == providerId) {
			return p.lock()->lookupName(moduleId);
		}
	}
	return "Module not found!";
}

shared_ptr<ctoot::synth::SynthControls> SynthServices::createControls(string name)
{
	shared_ptr<SynthControls> controls;
	for (auto& p : providers) {
		controls = p.lock()->createControls(name);
		if (controls) {
			controls->setProviderId(p.lock()->getProviderId());
			return controls;
		}
	}
	return {};
}

shared_ptr<ctoot::synth::MidiSynth> SynthServices::createSynth(weak_ptr<SynthControls> controls)
{
	MLOG("SynthServices trying to create synth from controls " + controls.lock()->getName());
	MLOG("Number of SynthServices providers: " + to_string(providers.size()));
	shared_ptr<MidiSynth> synth;
	for (auto& p : providers) {
		MLOG("Trying with provider " + p.lock()->getDescription() + " / " + p.lock()->getProviderName());
		synth = p.lock()->createSynth(controls);
		if (synth)
			return synth;
	}
	return {};
}

void SynthServices::scan()
{
	MLOG("Scanning for SynthServices...");
	auto prov = lookup(ctoot::synth::spi::SynthServiceProvider());
	providers.clear();
	for (auto& p : prov) {
		auto candidate = dynamic_pointer_cast<ctoot::synth::spi::SynthServiceProvider>(p.lock());
		if (candidate) {
			MLOG("Pushing back candidate " + candidate->getDescription() + " / " + candidate->getProviderName());
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

void SynthServices::printServiceDescriptors(string typeIdName)
{
    //accept(new ctoot::service::ServicePrinter(), clazz);
}
