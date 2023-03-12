#include <mpc/MpcBasicSoundPlayerControls.hpp>

#include <control/Control.hpp>

using namespace ctoot::mpc;
using namespace std;

MpcBasicSoundPlayerControls::MpcBasicSoundPlayerControls(weak_ptr<ctoot::mpc::MpcSampler> sampler, shared_ptr<ctoot::audio::mixer::AudioMixer> mixer, weak_ptr<ctoot::mpc::MpcVoice> voice)
	: ctoot::control::CompoundControl(9, "MpcBasicSoundPlayerChannel")
{
	this->sampler = sampler;
	this->mixer = mixer;
	this->voice = voice;
}

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
