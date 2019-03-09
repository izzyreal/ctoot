#include <synth/synths/multi/MultiMidiSynthObserver.hpp>
#include <synth/SynthChannel.hpp>
#include <synth/SynthChannelControls.hpp>
#include <synth/SynthChannelServices.hpp>
#include <synth/synths/multi/MultiMidiSynth.hpp>
#include <synth/synths/multi/MultiSynthControls.hpp>


//#include <mpc/MpcSoundPlayerChannel.hpp>
//#include <MpcBasicSoundPlayerChannel.hpp>
//#include <MpcSoundPlayerControls.hpp>
//#include <MpcBasicSoundPlayerControls.hpp>

using namespace ctoot::synth::synths::multi;
using namespace std;

MultiMidiSynthObserver::MultiMidiSynthObserver(MultiMidiSynth *mms, weak_ptr<MultiSynthControls> controls)
    : mms(mms)
    , controls(controls)
{
}


void MultiMidiSynthObserver::update(moduru::observer::Observable* obs, std::any a)
{
	try {
		auto chan = std::any_cast<int>(a);
		if (chan < 0 || chan > 15) return;

		//temp limitation! remove once things are better.
		//if (chan > 4) return;

		auto channelControls = controls.lock()->getChannelControls(chan).lock();

		if (channelControls) {
			auto synthChannel = ctoot::synth::SynthChannelServices::createSynthChannel(channelControls);
			/*
			shared_ptr<SynthChannel> synthChannel;
			if (chan < 4) {
				synthChannel = make_shared<ctoot::mpc::MpcSoundPlayerChannel>(dynamic_pointer_cast<ctoot::mpc::MpcSoundPlayerControls>(channelControls));
			}
			else {
				synthChannel = make_shared<ctoot::mpc::MpcBasicSoundPlayerChannel>(dynamic_pointer_cast<ctoot::mpc::MpcBasicSoundPlayerControls>(channelControls));
			}
			*/
			if (!synthChannel) {
				string msg = "No SynthChannel for SynthControls " + channelControls->getName();
				MLOG(msg);
			}
			else {
				synthChannel->setLocation(mms->getLocation() + " Channel " + to_string(1 + chan));
				synthChannel->addObserver(channelControls.get());
			}
			mms->setChannel(chan, synthChannel);
		}
		else {
			mms->setChannel(chan, shared_ptr<SynthChannel>());
		}
	}
	catch (const std::bad_any_cast& e) {
		e.what();
	}
}

MultiMidiSynthObserver::~MultiMidiSynthObserver() {
}
