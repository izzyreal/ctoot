#include <audio/system/DefaultAudioSystem.hpp>
#include <audio/system/AudioDevice.hpp>
#include <audio/system/AudioSystemObserver.hpp>

#include <Logger.hpp>

using namespace ctoot::audio::system;
using namespace std;

DefaultAudioSystem::DefaultAudioSystem() 
{
	autoConnect = true;
	observer = new AudioSystemObserver(this);
}

void DefaultAudioSystem::addAudioDevice(std::weak_ptr<AudioDevice> device)
{
	MLOG("Trying to add device " + device.lock()->getName());
	checkUniqueDeviceName(device);
	devices.push_back(device);
	setChanged();
	notifyObservers(device);
	device.lock()->addObserver(observer);
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
	device.lock()->deleteObserver(observer);
	int index = 0;
	for (auto& d : devices) {
		if (d.lock() == device.lock()) break;
		index++;
	}
	if (index >= devices.size()) return;
	devices.erase(devices.begin() + index);
	setChanged();
	notifyObservers(device);
}

vector<std::weak_ptr<AudioDevice>> DefaultAudioSystem::getAudioDevices()
{
	return devices;
}

vector<std::weak_ptr<AudioInput>> DefaultAudioSystem::getAudioInputs()
{
	vector<std::weak_ptr<AudioInput>> inputs;
	for (auto& device : devices) {
		for (auto& i : device.lock()->getAudioInputs())
			inputs.push_back(i);
	}
	return inputs;
}

vector<std::weak_ptr<AudioOutput>> DefaultAudioSystem::getAudioOutputs()
{
	vector<std::weak_ptr<AudioOutput>> outputs;
	for (auto& device : devices) {
			for (auto& output : device.lock()->getAudioOutputs())
				outputs.push_back(output);
	}
	return outputs;
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

DefaultAudioSystem::~DefaultAudioSystem() {
	if (observer != nullptr) {
		delete observer;
	}
}
