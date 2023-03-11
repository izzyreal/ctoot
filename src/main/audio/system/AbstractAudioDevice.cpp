#include <audio/system/AbstractAudioDevice.hpp>
#include <audio/system/AudioInput.hpp>
#include <audio/system/AudioOutput.hpp>

using namespace ctoot::audio::system;
using namespace std;

string AbstractAudioDevice::getName()
{
    return name;
}

string AbstractAudioDevice::toString()
{
	return name;
}
