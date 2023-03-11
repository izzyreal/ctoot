#include <audio/system/DefaultAudioSystem.hpp>
#include <audio/system/AudioDevice.hpp>

#include <Logger.hpp>

#include <stdexcept>

using namespace ctoot::audio::system;
using namespace std;

DefaultAudioSystem::DefaultAudioSystem() 
{
	autoConnect = true;
}

void DefaultAudioSystem::addAudioDevice(std::weak_ptr<AudioDevice> device)
{
	checkUniqueDeviceName(device);
	devices.push_back(device);
}

void DefaultAudioSystem::checkUniqueDeviceName(std::weak_ptr<AudioDevice> device)
{
	for (auto& d : devices) {
		if (d.lock()->getName().compare(device.lock()->getName()) == 0) {
			string exc = "An AudioDevice named " + device.lock()->getName() + " already exists";
			throw std::invalid_argument(exc.c_str());
		}
	}
}

void DefaultAudioSystem::removeAudioDevice(std::weak_ptr<AudioDevice> device)
{
	int index = 0;
	for (auto& d : devices) {
		if (d.lock() == device.lock()) break;
		index++;
	}
	if (index >= devices.size()) return;
	devices.erase(devices.begin() + index);
}

void DefaultAudioSystem::setAutoConnect(bool autoConnect)
{
    this->autoConnect = autoConnect;
}

void DefaultAudioSystem::close()
{
	for (auto& device : devices)
		device.lock()->closeAudio();
}
