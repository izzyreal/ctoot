#include <mpc/MpcBasicSoundPlayerControls.hpp>

#include <mpc/MpcEnvelopeControls.hpp>
#include <mpc/MpcSoundOscillatorControls.hpp>
#include <control/ControlRow.hpp>
#include <control/Control.hpp>

using namespace ctoot::mpc;
using namespace std;

MpcBasicSoundPlayerControls::MpcBasicSoundPlayerControls(weak_ptr<ctoot::mpc::MpcSampler> sampler, shared_ptr<ctoot::audio::mixer::AudioMixer> mixer, weak_ptr<ctoot::mpc::MpcVoice> voice) 
	: ctoot::synth::SynthChannelControls(MPC_BASIC_SOUND_PLAYER_CHANNEL_ID, "MpcBasicSoundPlayerChannel")
{
	this->sampler = sampler;
	this->mixer = mixer;
	this->voice = voice;
}

const int MpcBasicSoundPlayerControls::MPC_BASIC_SOUND_PLAYER_CHANNEL_ID;

string& MpcBasicSoundPlayerControls::NAME()
{
    return NAME_;
}
string MpcBasicSoundPlayerControls::NAME_ = "MpcBasicSoundPlayer";

weak_ptr<ctoot::mpc::MpcSampler> MpcBasicSoundPlayerControls::getSampler()
{
    return sampler;
}

weak_ptr<ctoot::audio::mixer::AudioMixer> MpcBasicSoundPlayerControls::getMixer()
{
    return mixer;
}

weak_ptr<ctoot::mpc::MpcVoice> MpcBasicSoundPlayerControls::getVoice()
{
    return voice;
}

MpcBasicSoundPlayerControls::~MpcBasicSoundPlayerControls() {
}
