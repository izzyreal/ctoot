#include <audio/server/AudioServer.hpp>

#include <Logger.hpp>

using namespace ctoot::audio::server;
using namespace std;

AudioServer::AudioServer() {
	log4cplus::Initializer initializer;
	log4cplus::BasicConfigurator config;
	config.configure();
	logger = log4cplus::Logger::getRoot();
}

float AudioServer::getSampleRate() {
	return sampleRate;
}

void AudioServer::setSampleRate(int rate) {
	sampleRate = static_cast<float>(rate);
	for (auto& b : buffers)
		b->setSampleRate(sampleRate);
}

const std::vector<IOAudioProcess*>& AudioServer::getActiveInputs() {
	return activeInputs;
}

const std::vector<IOAudioProcess*>& AudioServer::getActiveOutputs() {
	return activeOutputs;
}

const std::vector<ctoot::audio::core::AudioBuffer*>& AudioServer::getBuffers() {
	return buffers;
}

const unsigned int AudioServer::getBufferSize() {
	return bufferSize;
}

ctoot::audio::core::AudioBuffer* AudioServer::createAudioBuffer(string name) {
	buffers.push_back(new ctoot::audio::core::AudioBuffer(name, 2, bufferSize, sampleRate));
	return buffers.back();
}

void AudioServer::resizeBuffers(int newSize) {
	bufferSize = newSize;
	for (auto& b : buffers) {
		b->changeSampleCount(bufferSize, false);
	}
}

void AudioServer::removeAudioBuffer(ctoot::audio::core::AudioBuffer* buffer)
{
	for (int i = 0; i < buffers.size(); i++) {
		if (buffers[i] == buffer) {
			buffers.erase(buffers.begin() + i);
			break;
		}
	}
}

AudioServer::~AudioServer() {
	for (auto& b : buffers) {
		if (b != nullptr) {
			delete b;
		}
	}
}
