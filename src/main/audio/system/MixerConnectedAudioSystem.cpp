#include "MixerConnectedAudioSystem.hpp"

#include <audio/mixer/AudioMixer.hpp>
#include <audio/mixer/AudioMixerStrip.hpp>
#include <audio/system/AudioConnection.hpp>
#include <audio/system/AudioDevice.hpp>

using namespace ctoot::audio::system;
using namespace std;

MixerConnectedAudioSystem::MixerConnectedAudioSystem(shared_ptr<ctoot::audio::mixer::AudioMixer> mixer) 
{
    this->mixer = mixer;
    mixerControls = mixer->getMixerControls();
}
