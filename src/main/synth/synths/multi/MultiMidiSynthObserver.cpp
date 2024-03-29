#include <synth/synths/multi/MultiMidiSynthObserver.hpp>
#include <synth/SynthChannel.hpp>
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


void MultiMidiSynthObserver::update(moduru::observer::Observable* obs, nonstd::any a)
{
	try {
		auto chan = nonstd::any_cast<int>(a);
		
        if (chan < 0 || chan > 15)
            return;

		auto channelControls = controls.lock()->getChannelControls(chan).lock();

		if (channelControls) {
			auto synthChannel = ctoot::synth::SynthChannelServices::createSynthChannel(channelControls);
		
            if (!synthChannel)
            {
				MLOG("No SynthChannel for SynthControls " + channelControls->getName());
			}
			else
            {
				synthChannel->setLocation(mms->getLocation() + " Channel " + to_string(1 + chan));
				synthChannel->addObserver(channelControls.get());
			}
			mms->setChannel(chan, synthChannel);
		}
		else
        {
			mms->setChannel(chan, shared_ptr<SynthChannel>());
		}
	}
	catch (const std::exception& e)
    {
		string msg = e.what();
        MLOG("Could not update MultiMidiSynthObserver: " + msg);
	}
}
