#include "MpcSoundPlayerControls.hpp"

#include "MpcSampler.hpp"
#include <audio/mixer/AudioMixer.hpp>
#include <audio/server/AudioServer.hpp>

using namespace ctoot::mpc;
using namespace std;

MpcSoundPlayerControls::MpcSoundPlayerControls(
	weak_ptr<MpcSampler> sampler,
    int drumNumber,
    weak_ptr<ctoot::audio::mixer::AudioMixer> mixer,
    weak_ptr<ctoot::audio::server::AudioServer> server,
    ctoot::mpc::MpcMixerSetupGui* mixerSetupGui,
    std::vector<std::shared_ptr<MpcVoice>> voicesToUse) :
    ctoot::synth::SynthChannelControls(MPC_SOUND_PLAYER_CHANNEL_ID, NAME_),
    voices(voicesToUse)
{
	this->sampler = sampler;
	this->drumNumber = drumNumber;
	this->mixer = mixer;
	this->server = server;
	this->mixerSetupGui = mixerSetupGui;
}

const int MpcSoundPlayerControls::MPC_SOUND_PLAYER_CHANNEL_ID;
string MpcSoundPlayerControls::NAME_ = "MpcSoundPlayer";

std::vector<std::shared_ptr<MpcVoice>> MpcSoundPlayerControls::getVoices()
{
	return voices;
}

weak_ptr<ctoot::mpc::MpcSampler> MpcSoundPlayerControls::getSampler()
{
    return sampler;
}

int MpcSoundPlayerControls::getDrumIndex()
{
    return drumNumber;
}

weak_ptr<ctoot::audio::mixer::AudioMixer> MpcSoundPlayerControls::getMixer()
{
    return mixer;
}

ctoot::audio::server::AudioServer* MpcSoundPlayerControls::getServer()
{
    return server.lock().get();
}

ctoot::mpc::MpcMixerSetupGui* MpcSoundPlayerControls::getMixerSetupGui() {
	return mixerSetupGui;
}
