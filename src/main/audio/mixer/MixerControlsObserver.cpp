#include <audio/mixer/MixerControlsObserver.hpp>
#include <audio/mixer/Mutation.hpp>
#include <audio/mixer/AudioMixer.hpp>

using namespace ctoot::audio::mixer;

MixerControlsObserver::MixerControlsObserver(AudioMixer* _mixer)
: mixer (_mixer)
{
}

void MixerControlsObserver::update(nonstd::any a)
{
    if (a.has_value() && a.type() == typeid(Mutation*))
    {
        auto m = nonstd::any_cast<Mutation*>(a);
		
        if (mixer->isEnabled() && mixer->getAudioServer().lock()->isRunning())
			mixer->getMutationQueue().try_enqueue(m);
		else
            mixer->processMutation(m);
	}
}
