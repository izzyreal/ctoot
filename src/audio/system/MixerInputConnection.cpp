#include <audio/system/MixerInputConnection.hpp>

#include <audio/mixer/AudioMixerStrip.hpp>
#include <audio/system/AudioOutput.hpp>
#include <audio/system/MixerConnectedAudioSystem.hpp>

using namespace ctoot::audio::system;
using namespace std;

MixerInputConnection::MixerInputConnection(MixerConnectedAudioSystem* mca, std::weak_ptr<AudioOutput> from, ctoot::audio::mixer::AudioMixerStrip* to, int flags) : AudioConnection(flags)
{
	if (!from.lock() || to == nullptr) {
		MLOG("MixerInputConnection constructor null argument");
		return;
	}
	this->from = from;
	this->to = to;
	try {
		to->setInputProcess(from);
	}
	catch (exception* e) {
		e->what();
		return;
	}
}

void MixerInputConnection::close()
{
	try {
		to->setInputProcess(std::weak_ptr<ctoot::audio::core::AudioProcess>());
	}
	catch (exception* e) {
		e->what();
	}
	from.reset();
	to = nullptr;
}

string MixerInputConnection::getOutputName()
{
    return from.lock()->getName();
}

string MixerInputConnection::getOutputLocation()
{
    return from.lock()->getLocation();
}

string MixerInputConnection::getInputName()
{
    return to->getName();
}

MixerInputConnection::~MixerInputConnection() {
}
