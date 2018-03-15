#include <synth/synths/multi/MultiMidiSynth.hpp>
#include <audio/system/AudioOutput.hpp>
#include <synth/SynthChannel.hpp>
#include <synth/synths/multi/MultiMidiSynthObserver.hpp>
#include <synth/synths/multi/MultiSynthControls.hpp>

using namespace ctoot::audio::system;
using namespace ctoot::synth::synths::multi;
using namespace std;

MultiMidiSynth::MultiMidiSynth(shared_ptr<MultiSynthControls> controls)
	: BasicMidiSynth(controls->getName())
{
	observer = new MultiMidiSynthObserver(this, controls);
	controls->addObserver(observer);
}

void MultiMidiSynth::setChannel(int chan, shared_ptr<ctoot::synth::SynthChannel> synthChannel)
{
	auto old = dynamic_pointer_cast<AudioOutput>(getChannel(chan).lock());
	if (old) {
		removeAudioOutput(old);
	}
	BasicMidiSynth::setChannel(chan, synthChannel);
	auto newChannel = dynamic_pointer_cast<ctoot::audio::system::AudioOutput>(synthChannel);
	if (newChannel) {
		addAudioOutput(newChannel);
	}
}

MultiMidiSynth::~MultiMidiSynth() {
	if (observer != nullptr) {
		delete observer;
	}
}
