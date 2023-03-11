#include <synth/channels/AllTootSynthChannelsServiceProvider.hpp>

#include <synth/SynthChannelControls.hpp>

#include <mpc/MpcBasicSoundPlayerChannel.hpp>
#include <mpc/MpcBasicSoundPlayerControls.hpp>
#include <mpc/MpcSoundPlayerChannel.hpp>
#include <mpc/MpcSoundPlayerControls.hpp>

#include <synth/id/TootSynthControlsId.hpp>

using namespace ctoot::synth::channels;
using namespace std;

AllTootSynthChannelsServiceProvider::AllTootSynthChannelsServiceProvider()
	: ctoot::synth::spi::TootSynthChannelServiceProvider("Toot Synth Channels", "0.2")
{
	addControls("ctoot::synth::SynthChannelControls", ctoot::mpc::MpcBasicSoundPlayerControls::MPC_BASIC_SOUND_PLAYER_CHANNEL_ID, "ctoot::mpc::MpcBasicSoundPlayerControls", "MPC Basic", "0.2");
	addControls("ctoot::synth::SynthChannelControls", ctoot::mpc::MpcSoundPlayerControls::MPC_SOUND_PLAYER_CHANNEL_ID, "ctoot::mpc::MpcSoundPlayerControls", "MPC", "0.2");
}

shared_ptr<ctoot::synth::SynthChannel> AllTootSynthChannelsServiceProvider::createSynthChannel(weak_ptr<ctoot::synth::SynthChannelControls> c)
{
	auto name = c.lock()->getName();

	if (name.compare("MpcBasicSoundPlayerChannel") == 0) {
		return make_shared<ctoot::mpc::MpcBasicSoundPlayerChannel>(dynamic_pointer_cast<ctoot::mpc::MpcBasicSoundPlayerControls>(c.lock()));
	}
	if (name.length() >= 14 && name.substr(0, 14).compare("MpcSoundPlayer") == 0) {
		return make_shared<ctoot::mpc::MpcSoundPlayerChannel>(dynamic_pointer_cast<ctoot::mpc::MpcSoundPlayerControls>(c.lock()));
	}
		return {};
}
