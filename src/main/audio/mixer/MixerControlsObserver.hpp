#pragma once
#include <observer/Observer.hpp>

namespace ctoot::audio::mixer
{
class AudioMixer;
class MixerControlsObserver
: public moduru::observer::Observer
{
    
public:
    virtual void update(nonstd::any);
    
    MixerControlsObserver(AudioMixer*);
    
public:
    AudioMixer* mixer;
    
private:
    friend class AudioMixer;
    friend class AudioMixer_createStrip_1;
    friend class AudioMixer_DefaultMixerInterconnection;
    friend class AudioMixer_DefaultMixerInterconnection_DefaultMixerInterconnection_1;
    friend class AudioMixer_DefaultMixerInterconnection_DefaultMixerInterconnection_2;
};
}
