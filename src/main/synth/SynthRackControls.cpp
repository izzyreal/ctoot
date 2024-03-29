#include <synth/SynthRackControls.hpp>
#include <observer/Observable.hpp>
#include <control/CompoundControl.hpp>
#include <control/id/ProviderId.hpp>
#include <synth/SynthControls.hpp>

using namespace ctoot::synth;
using namespace std;

SynthRackControls::SynthRackControls(int nsynths)
	: CompoundControl(2, "Synth Rack")
{
	this->nsynths = nsynths;
	synthControls = vector<weak_ptr<SynthControls>>(nsynths);
}

int SynthRackControls::size()
{
    return nsynths;
}

weak_ptr<SynthControls> SynthRackControls::getSynthControls(int synth)
{
    return synthControls[synth];
}

void SynthRackControls::setSynthControls(int synth, shared_ptr<SynthControls> controls)
{
	auto old = synthControls[synth];
	if (old.lock()) {
		remove(old);
	}
	weak_ptr<SynthControls> weakRef = controls;
	if (controls) {
		string name = controls->getName();
		if (find(name).lock()) {
			disambiguate(controls);
			controls->setAnnotation(name);
		}
		add(std::move(controls));
	}
	synthControls[synth] = weakRef;
	
	notifyObservers(synth);
}

void SynthRackControls::removeAll()
{
	for (auto synth = 0; synth < nsynths; synth++) {
		setSynthControls(synth, nullptr);
	}
}

int SynthRackControls::getProviderId()
{
	return ctoot::control::id::ProviderId::TOOT_PROVIDER_ID;
}

bool SynthRackControls::isPluginParent()
{
    return true;
}

string SynthRackControls::getPersistenceDomain()
{
	return "synth";
}

SynthRackControls::~SynthRackControls() {
	for (auto& s : synthControls)
		s.reset();
}
