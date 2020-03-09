#include <synth/SynthRackObserver.hpp>

#include <audio/system/AudioDevice.hpp>
#include <midi/core/MidiDevice.hpp>
#include <midi/core/MidiInput.hpp>
#include <midi/core/MidiPort.hpp>
#include <midi/core/MidiTransport.hpp>
#include <synth/MidiSynth.hpp>
#include <synth/synths/multi/MultiMidiSynth.hpp>
#include <synth/SynthControls.hpp>
#include <synth/SynthRack.hpp>
#include <synth/SynthRackControls.hpp>
#include <synth/SynthServices.hpp>

//#include <MpcMultiMidiSynth.hpp>
//#include <MpcMultiSynthControls.hpp>

using namespace ctoot::synth;
using namespace ctoot::synth::synths::multi;
using namespace std;

#include <iostream>

SynthRackObserver::SynthRackObserver(SynthRack* sr, weak_ptr<SynthRackControls> controls)
    : sr(sr)
    , controls(controls)
{
}

void SynthRackObserver::update(moduru::observer::Observable* obs, nonstd::any obj)
{
	MLOG("SynthRackObserver::update()");
	try {
		int nsynth = nonstd::any_cast<int>(obj);
		if (nsynth < 0 || nsynth >= sr->synths.size()) return;
		auto synthControls = controls.lock()->getSynthControls(nsynth).lock();
		if (synthControls) {
			auto synth = SynthServices::createSynth(synthControls);
			//auto synth = make_shared<ctoot::mpc::MpcMultiMidiSynth>(dynamic_pointer_cast<MultiSynthControls>(synthControls));
			if (!synth) {
				MLOG("Synth creation failed!");
				std::cout << "synth == nullptr!" << endl;
				return;
			}
			else {
				MLOG("Synth creation succeeded: " + synth->getName());
				char c = 'A' + nsynth;
				string letterStr = "  ";
				letterStr[0] = c;
				synth->setLocation(synthControls->getName() + " " + letterStr);
			}
			sr->setMidiSynth(nsynth, synth);
		}
		else {
			sr->setMidiSynth(nsynth, shared_ptr<ctoot::synth::MidiSynth>());
		}
	}
	catch (const std::exception& e) {
	}
}

SynthRackObserver::~SynthRackObserver() {
}
