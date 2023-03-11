#include <audio/system/AbstractAudioDevice.hpp>
#include <audio/system/AudioInput.hpp>
#include <audio/system/AudioOutput.hpp>

using namespace ctoot::audio::system;
using namespace std;

vector<std::weak_ptr<AudioOutput>> AbstractAudioDevice::getAudioOutputs()
{
	std::vector<std::weak_ptr<AudioOutput>> res;
	for (auto& o : outputs)
		res.push_back(o);
    return res;
}

string AbstractAudioDevice::getName()
{
    return name;
}

string AbstractAudioDevice::toString()
{
	return name;
}
