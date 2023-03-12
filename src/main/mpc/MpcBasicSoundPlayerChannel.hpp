#pragma once
#include <synth/SynthChannel.hpp>
#include <audio/mixer/AudioMixerStrip.hpp>

#include <memory>

namespace ctoot::mpc {

class MpcSampler;
class MpcSound;
class MpcBasicSoundPlayerControls;
class MpcVoice;

class MpcBasicSoundPlayerChannel final
: public ctoot::synth::SynthChannel
{
    
private:
    std::shared_ptr<ctoot::mpc::MpcSampler> sampler;
    std::shared_ptr<ctoot::mpc::MpcVoice> voice;
    std::shared_ptr<ctoot::mpc::MpcSound> tempVars;
    
    std::shared_ptr<ctoot::audio::mixer::AudioMixer> mixer;
    std::shared_ptr<ctoot::audio::fader::FaderControl> fader;
    
public:
    void finishVoice();
    void setLocation(std::string location) override;
    void noteOn(int soundNumber, int velocity) override;
    void mpcNoteOn(int soundNumber, int velocity, int frameOffset);
    void noteOff(int note) override;
    void allNotesOff() override;

    void connectVoice();
    
    MpcBasicSoundPlayerChannel(std::weak_ptr<MpcBasicSoundPlayerControls> controls);
    
public:
    void noteOff(int pitch, int velocity) override;
    
};
}
