#include "ExternalAudioServer.hpp"
#include "StereoInputProcess.hpp"
#include "StereoOutputProcess.hpp"
#include "../core/ChannelFormat.hpp"

#include <iostream>
#include <Logger.hpp>


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

/*
void ExternalAudioServer::work(const float** InAudio, float** OutAudio, int nFrames, int inputChannels, int outputChannels) {
	std::vector<float> tempInL(nFrames);
	std::vector<float> tempInR(nFrames);
	std::vector<float*> tempInLR = { &tempInL[0], &tempInR[0] };
	if (inputChannels >= 2) {
		for (int i = 0; i < nFrames; i++) {
			tempInL[i] = InAudio[0][i];
			tempInR[i] = InAudio[1][i];
		}
	}
	work(&tempInLR[0], OutAudio, nFrames, inputChannels, outputChannels);
}


void ExternalAudioServer::work(float** InAudio, float** OutAudio, int nFrames, int inputChannels, int outputChannels) {
	LOG4CPLUS_TRACE(logger, LOG4CPLUS_TEXT("ExternalAudioServer::work1"));
	int channelsToProcess = static_cast<int>(activeInputs.size() < (inputChannels / 2) ? activeInputs.size() : (inputChannels / 2));
	if (activeInputs.size() != 0 && inputChannels >= 2) {
		float* inputBufferL = (float*)InAudio[0];
		float* inputBufferR = (float*)InAudio[1];
		if (activeInputs[0]->localBuffer.size() != nFrames * 2)
			activeInputs[0]->localBuffer.resize(nFrames * 2);
		int frameCounter = 0;
		for (int i = 0; i < nFrames * 2; i += 2) {
			activeInputs[0]->localBuffer[i] = inputBufferL[frameCounter];
			activeInputs[0]->localBuffer[i + 1] = inputBufferR[frameCounter++];
		}
	}

	client->work(nFrames);
	channelsToProcess = static_cast<int>(activeOutputs.size() < (outputChannels / 2) ? activeOutputs.size() : (outputChannels / 2));
	for (int output = 0; output < channelsToProcess; output++) {
		int counter = 0;
		for (int i = 0; i < nFrames; i++) {
			auto sampleL = activeOutputs[output]->localBuffer[counter++];
			auto sampleR = activeOutputs[output]->localBuffer[counter++];
			OutAudio[0][i] = (float)(sampleL);
			OutAudio[1][i] = (float)(sampleR);
		}
	}
}
*/

void ExternalAudioServer::work(float* inputBuffer, float* outputBuffer, int nFrames, int inputChannelCount, int outputChannelCount) {

	LOG4CPLUS_TRACE(logger, LOG4CPLUS_TEXT("ExternalAudioServer::work"));
	LOG4CPLUS_TRACE(logger, LOG4CPLUS_TEXT("nFrames           : ") << nFrames);
	LOG4CPLUS_TRACE(logger, LOG4CPLUS_TEXT("activeInputs.size : ") << (int)activeInputs.size());
	LOG4CPLUS_TRACE(logger, LOG4CPLUS_TEXT("activeOutputs.size: ") << (int)activeOutputs.size());
	LOG4CPLUS_TRACE(logger, LOG4CPLUS_TEXT("inputChannelCount : ") << (int)inputChannelCount);
	LOG4CPLUS_TRACE(logger, LOG4CPLUS_TEXT("outputChannelCount: ") << (int)outputChannelCount);

	for (auto& i : activeInputs) {
		if (i->localBuffer.size() != nFrames * 2) {
			i->localBuffer.resize(nFrames * 2);
		}
	}
	
	int sampleCounter = 0;
	const int inputsToProcess = min(inputChannelCount / 2, (int)activeInputs.size());
	for (int frame = 0; frame < nFrames; frame++) {
		for (int input = 0; input < inputChannelCount / 2; input++) {
			activeInputs[input]->localBuffer[sampleCounter++] = *inputBuffer++;
			activeInputs[input]->localBuffer[sampleCounter++] = *inputBuffer++;
		}
	}

	client->work(nFrames);
	sampleCounter = 0;
	const int outputsToProcess = min(outputChannelCount / 2, (int) activeOutputs.size());
	for (int frame = 0; frame < nFrames; frame++) {
		for (int output = 0; output < outputsToProcess / 2; output++) {
			*outputBuffer++ = activeOutputs[output]->localBuffer[sampleCounter++];
			*outputBuffer++ = activeOutputs[output]->localBuffer[sampleCounter++];
		}
	}
}

void ExternalAudioServer::work(double** InAudio, double** OutAudio, int nFrames, int outputChannels) {
	auto activeInputs = getActiveInputs();
	if (activeInputs.size() != 0) {
		double* inputBufferL = (double*)InAudio[0];
		double* inputBufferR = (double*)InAudio[1];
		if (activeInputs[0]->localBuffer.size() != nFrames * 2)
			activeInputs[0]->localBuffer.resize(nFrames * 2);
		int frameCounter = 0;
		for (int i = 0; i < nFrames * 2; i += 2) {
			activeInputs[0]->localBuffer[i] = inputBufferL[frameCounter];
			activeInputs[0]->localBuffer[i + 1] = inputBufferR[frameCounter++];
		}
	}
	int channelsToProcess = static_cast<int>(activeOutputs.size() < (outputChannels / 2) ? activeOutputs.size() : (outputChannels / 2));
	client->work(nFrames);
	for (int output = 0; output < channelsToProcess; output++) {
		int counter = 0;
		for (int i = 0; i < nFrames; i++) {
			auto sampleL = activeOutputs[output]->localBuffer[counter++];
			auto sampleR = activeOutputs[output]->localBuffer[counter++];
			OutAudio[(output * 2)][i] = sampleL;
			OutAudio[(output * 2) + 1][i] = sampleR;
		}
	}
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
