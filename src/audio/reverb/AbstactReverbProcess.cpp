#include "AbstactReverbProcess.hpp"

#include <audio/core/FloatDenormals.hpp>

#include <cassert>

#include <Logger.hpp>

using namespace ctoot::audio::reverb;
using namespace ctoot::audio::core;

int AbstractReverbProcess::processAudio(AudioBuffer* buffer) {
	cacheVariables();
	//buffer->monoToStereo();
	auto samplesL = buffer->getChannel(0);
	auto samplesR = buffer->getChannel(1);

	for (int i = 0; i < buffer->getSampleCount(); i++) {
		reverb((*samplesL)[i], (*samplesR)[i]);
		(*samplesL)[i] = left();
		(*samplesR)[i] = right();
	}
	return AUDIO_OK;
	/*
	std::vector<float> outputL(nFrames);
	std::vector<float> outputR(nFrames);
	std::vector<float*> outputs{ &outputL[0], &outputR[0] };

	float* inputL = &(*samplesL)[0];
	float* inputR = &(*samplesL)[0];
	std::vector<float*> inputs{ &inputL[0], &inputR[0] };

	em_verb.processVec(&inputs, &outputs, nFrames);
	for (int i = 0; i < nFrames; i++) {
		(*samplesL)[i] = outputL[i];
		(*samplesR)[i] = outputR[i];
	}

	return AUDIO_OK;
	*/
}

float Filter::filter(float sample, float k) {
	return zm1 = FloatDenormals::zeroDenorm(k * (zm1 - sample) + sample);
}

Delay::Delay() {
}

Delay::Delay(int length) {
	line = std::vector<float>(length);
	maxLength = length;
	this->length = length;
}

float Delay::read() {
	return line[head];
}
void Delay::append(float sample) {
	line[head++] = sample;
	if (head > length - 1) head = 0;
}

float Delay::delay(float sample) {
	float s = read();
	append(sample);
	return s;
}

float Delay::tap(int zm) {
	assert(zm > 0);
	assert(zm < length);
	int p = head - zm;
	if (p < 0) p += length;
	return line[p];
}

void Delay::resize(float factor) {
	length = (int)(factor * maxLength);
	if (head > length - 1) head = 0; // may glitch!            
}


Diffuser::Diffuser()
{
}

Diffuser::Diffuser(int length)
	: Delay(length - 1)
{
}

float Diffuser::diffuse(float sample, float k) {
	float a = sample - k * b;
	float out = k * a + b;
	b = FloatDenormals::zeroDenorm(delay(a));
	return out;
}

// TODO remove -1 in ctor, remove b
// is denormal needed?
// signed are different! dattoro is odd one out
float Diffuser::diffuse2(float sample, float k) {
	float out = read();
	float in = sample + k * out;
	append(in);
	return out - k * in;
}
