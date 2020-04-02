#include "ExternalAudioServer.hpp"
#include "StereoInputProcess.hpp"
#include "StereoOutputProcess.hpp"
#include "../core/ChannelFormat.hpp"

#include <iostream>

#include <System.hpp>

//#include <log4cplus/log4cplus.h>

using namespace ctoot::audio::server;
using namespace std;

ExternalAudioServer::ExternalAudioServer() {
}

void ExternalAudioServer::start() {
	if (running) return;
	client->setEnabled(true);
	running = true;
}

void ExternalAudioServer::stop() {
	running = false;
}

bool ExternalAudioServer::isRunning() {
	return running;
}

void ExternalAudioServer::close() {
	activeInputs.clear();
	activeOutputs.clear();
}

void ExternalAudioServer::work() {
	if (buffers.size() < 1) return;
	client->work(buffers[0]->getSampleCount());
}

void ExternalAudioServer::work(float* inputBuffer, float* outputBuffer, int nFrames, int inputChannelCount, int outputChannelCount) {
	if (!running) {
		return;
	}
	
	for (auto& i : activeInputs) {
		if (i->localBuffer.size() != nFrames * 2) {
			i->localBuffer.resize(nFrames * 2);
		}
	}
	
	int sampleCounter = 0;
	const int inputsToProcess = min(inputChannelCount / 2, (int)activeInputs.size());
	for (int frame = 0; frame < nFrames; frame++) {
		for (int input = 0; input < inputsToProcess; input++) {
			activeInputs[input]->localBuffer[sampleCounter++] = *inputBuffer++;
			activeInputs[input]->localBuffer[sampleCounter++] = *inputBuffer++;
		}
	}

	client->work(nFrames);

	auto originalOutputBuffer = outputBuffer;
	const int outputsToProcess = outputChannelCount / 2;
	for (int frame = 0; frame < nFrames; frame++) {
		for (int output = 0; output < outputsToProcess; output++) {
			if (output >= activeOutputs.size()) {
				*outputBuffer++ = 0.0f;
				*outputBuffer++ = 0.0f;
				continue;
			}
			*outputBuffer++ = activeOutputs[output]->localBuffer[(frame * 2)];
			*outputBuffer++ = activeOutputs[output]->localBuffer[(frame * 2) + 1];
		}
	}
	outputBuffer = originalOutputBuffer;
}

void ExternalAudioServer::work(const float** inputBuffer, float** outputBuffer, int nFrames, int inputChannelCount, int outputChannelCount) {
	if (!running) {
		return;
	}
	
	for (auto& i : activeInputs) {
		if (i->localBuffer.size() != nFrames * 2) {
			i->localBuffer.resize(nFrames * 2);
		}
	}
	
	int sampleCounter = 0;
	const int inputsToProcess = min(inputChannelCount / 2, (int)activeInputs.size());
	for (int frame = 0; frame < nFrames; frame++) {
		for (int input = 0; input < inputsToProcess; input += 2) {
			activeInputs[input]->localBuffer[sampleCounter++] = inputBuffer[input][frame];
			activeInputs[input]->localBuffer[sampleCounter++] = inputBuffer[input + 1][frame];
		}
	}

	client->work(nFrames);

	auto originalOutputBuffer = outputBuffer;
	const int outputsToProcess = outputChannelCount * 0.5;
	for (int frame = 0; frame < nFrames; frame++) {
		for (int output = 0; output < outputsToProcess; output += 2) {
			if (output >= activeOutputs.size()) {
				outputBuffer[output][frame] = 0.0f;
				outputBuffer[output + 1][frame] = 0.0f;
				continue;
			}
			const auto frame_x2 = frame * 2;
			outputBuffer[output][frame] = activeOutputs[output]->localBuffer[frame_x2];
			outputBuffer[output + 1][frame] = activeOutputs[output]->localBuffer[frame_x2 + 1];
		}
	}
	outputBuffer = originalOutputBuffer;
}

void ExternalAudioServer::setClient(weak_ptr<AudioClient> client) {
	auto lClient = client.lock();
	this->client = lClient.get();
}

vector<string> ExternalAudioServer::getAvailableOutputNames() {
	vector<string> res{ "STEREO OUT", "ASSIGNABLE MIX OUT 1/2", "ASSIGNABLE MIX OUT 3/4", "ASSIGNABLE MIX OUT 5/6", "ASSIGNABLE MIX OUT 7/8" };
	return res;
}

vector<string> ExternalAudioServer::getAvailableInputNames() {
	vector<string> res{ "RECORD IN" };
	return res;
}

IOAudioProcess* ExternalAudioServer::openAudioOutput(string name, string label) {
	activeOutputs.push_back(new StereoOutputProcess(name, false, "ExternalAudioServer"));
	return activeOutputs.back();
}

IOAudioProcess* ExternalAudioServer::openAudioInput(string name, string label) {
	activeInputs.push_back(new StereoInputProcess(name, false, "ExternalAudioServer"));
	return activeInputs.back();
}

void ExternalAudioServer::closeAudioOutput(ctoot::audio::server::IOAudioProcess* output) {
	output->close();
	for (int i = 0; i < activeOutputs.size(); i++) {
		if (activeOutputs[i] == output) {
			activeOutputs.erase(activeOutputs.begin() + i);
			break;
		}
	}
}

void ExternalAudioServer::closeAudioInput(ctoot::audio::server::IOAudioProcess* input) {
	input->close();
	for (int i = 0; i < activeInputs.size(); i++) {
		if (activeInputs[i] == input) {
			activeInputs.erase(activeInputs.begin() + i);
			break;
		}
	}
}

float ExternalAudioServer::getLoad() {
	return 0;
}

int ExternalAudioServer::getInputLatencyFrames() {
	return bufferSize;
}

int ExternalAudioServer::getOutputLatencyFrames() {
	return bufferSize;
}

int ExternalAudioServer::getTotalLatencyFrames() {
	return getInputLatencyFrames() + getOutputLatencyFrames();
}
