#include "ExternalAudioServer.hpp"
#include "StereoInputProcess.hpp"
#include "StereoOutputProcess.hpp"
#include "../core/ChannelFormat.hpp"

#include <iostream>

#include <System.hpp>

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
	LOG4CPLUS_TRACE(logger, LOG4CPLUS_TEXT("Entering ExternalAudioServer::work()..."));
	if (!running) {
		LOG4CPLUS_TRACE(logger, LOG4CPLUS_TEXT("ExternalAudioServer is not running"));
		return;
	}
	else {
		LOG4CPLUS_TRACE(logger, LOG4CPLUS_TEXT("ExternalAudioServer is running, continuing work() routine..."));
	}

	LOG4CPLUS_TRACE(logger, LOG4CPLUS_TEXT("nFrames            : ") << nFrames);
	LOG4CPLUS_TRACE(logger, LOG4CPLUS_TEXT("activeInputs.size  : ") << (int)activeInputs.size());
	LOG4CPLUS_TRACE(logger, LOG4CPLUS_TEXT("activeOutputs.size : ") << (int)activeOutputs.size());
	LOG4CPLUS_TRACE(logger, LOG4CPLUS_TEXT("inputChannelCount  : ") << (int)inputChannelCount);
	LOG4CPLUS_TRACE(logger, LOG4CPLUS_TEXT("outputChannelCount : ") << (int)outputChannelCount);

	LOG4CPLUS_TRACE(logger, LOG4CPLUS_TEXT("Verifying if ctoot input buffers are correct size..."));
	for (auto& i : activeInputs) {
		if (i->localBuffer.size() != nFrames * 2) {
			LOG4CPLUS_TRACE_STR(logger, LOG4CPLUS_STRING_TO_TSTRING("Resizing buffer of input: " + i->getName()));
			i->localBuffer.resize(nFrames * 2);
		}
	}
	
	int sampleCounter = 0;
	const int inputsToProcess = min(inputChannelCount / 2, (int)activeInputs.size());
	LOG4CPLUS_TRACE(logger, LOG4CPLUS_TEXT("Inputs to process: ") << inputsToProcess);
	for (int frame = 0; frame < nFrames; frame++) {
		for (int input = 0; input < inputsToProcess; input++) {
			activeInputs[input]->localBuffer[sampleCounter++] = *inputBuffer++;
			activeInputs[input]->localBuffer[sampleCounter++] = *inputBuffer++;
		}
	}
	LOG4CPLUS_TRACE(logger, LOG4CPLUS_TEXT("Finished processing inputs"));

	LOG4CPLUS_TRACE(logger, LOG4CPLUS_TEXT("Calling client->work()..."));
	client->work(nFrames);
	LOG4CPLUS_TRACE(logger, LOG4CPLUS_TEXT("client->work() finished"));

	const int outputsToProcess = outputChannelCount / 2;
	LOG4CPLUS_TRACE(logger, LOG4CPLUS_TEXT("outputsToProcess: ") << outputsToProcess);

	auto originalOutputBuffer = outputBuffer;

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

	LOG4CPLUS_TRACE(logger, LOG4CPLUS_TEXT("Finished processing outputs"));
	LOG4CPLUS_TRACE(logger, LOG4CPLUS_TEXT("Leaving ExternalAudioServer::work()"));
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
