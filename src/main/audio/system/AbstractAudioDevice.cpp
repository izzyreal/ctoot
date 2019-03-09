#include <audio/system/AbstractAudioDevice.hpp>
#include <audio/system/AudioInput.hpp>
#include <audio/system/AudioOutput.hpp>

using namespace ctoot::audio::system;
using namespace std;

AbstractAudioDevice::AbstractAudioDevice(string name)
{
	this->name = name;
}

vector<std::weak_ptr<AudioInput>> AbstractAudioDevice::getAudioInputs()
{
	std::vector<std::weak_ptr<AudioInput>> res;
	for (auto& i : inputs)
		res.push_back(i);
	return res;
}

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

void AbstractAudioDevice::addAudioInput(std::shared_ptr<AudioInput> input)
{
	inputs.push_back(std::move(input));
	setChanged();
	notifyObservers(input);
}

void AbstractAudioDevice::removeAudioInput(std::weak_ptr<AudioInput> input)
{
	int counter = 0;
	for (auto& i : inputs) {
		if (i == input.lock()) {
			break;
		}
		counter++;
	}
	if (counter >= inputs.size()) return;
	inputs.erase(inputs.begin() + counter);
	setChanged();
	notifyObservers(input);
}

void AbstractAudioDevice::addAudioOutput(std::shared_ptr<AudioOutput> output)
{
	outputs.push_back(std::move(output));
	setChanged();
	notifyObservers(output);
}

void AbstractAudioDevice::removeAudioOutput(std::weak_ptr<AudioOutput> output)
{
	int counter = 0;
	for (auto& o : outputs) {
		if (o == output.lock()) {
			break;
		}
		counter++;
	}
	if (counter >= outputs.size()) return;
	outputs.erase(outputs.begin() + counter);
	setChanged();
	notifyObservers(output);
}

AbstractAudioDevice::~AbstractAudioDevice() {
}
