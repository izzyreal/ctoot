#include <audio/system/AudioSystemObserver.hpp>
#include <audio/system/DefaultAudioSystem.hpp>

//#include <Logger.hpp>

using namespace ctoot::audio::system;

AudioSystemObserver::AudioSystemObserver(DefaultAudioSystem* das)
{
	this->das = das;
}

void AudioSystemObserver::update(moduru::observer::Observable* obs, nonstd::any arg)
{
	//MLOG("Update, observable " + std::string(typeid(obs).name()));
	das->notifyObservers(arg);
}

AudioSystemObserver::~AudioSystemObserver() {
	das = nullptr;
}
