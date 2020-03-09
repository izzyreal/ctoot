#include <audio/mixer/MixerControlsObserver.hpp>
#include <audio/mixer/Mutation.hpp>
#include <audio/mixer/AudioMixer.hpp>

using namespace ctoot::audio::mixer;

MixerControlsObserver::MixerControlsObserver(AudioMixer* am)
{
	this->am = am;
}

void MixerControlsObserver::update(nonstd::any a)
{
	Mutation* m = nullptr;
	try {
		m = nonstd::any_cast<Mutation*>(a);
	}
	catch (const std::exception& e) {
		//printf(e.what());
		return;
	}
	if (m != nullptr) {
		if (am->isEnabled() && am->getAudioServer().lock()->isRunning()) {
			am->getMutationQueue().try_enqueue(m);
		}
		else {
			am->processMutation(m);
		}
	}
}
