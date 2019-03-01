#include "MeterProcess.hpp"

#include <audio/core/AudioBuffer.hpp>
#include <audio/meter/MeterControls.hpp>

#include <cmath>

using namespace ctoot::audio::meter;
using namespace std;

MeterProcess::MeterProcess(weak_ptr<MeterControls> controls) 
{
    this->controls = controls;
}

int MeterProcess::processAudio(::ctoot::audio::core::AudioBuffer* buffer)
{
    auto nc = buffer->getChannelCount();
    auto ns = buffer->getSampleCount();
    check(buffer);
    for (int c = 0; c < nc; c++) {
        auto samples = buffer->getChannel(c);
        detectOvers(c, samples, ns);
        detectPeak(c, samples, ns);
        detectAverage(c, samples, ns);
    }
    return AUDIO_OK;
}

void MeterProcess::check(::ctoot::audio::core::AudioBuffer* buffer)
{
	auto ms = buffer->getSampleCount() / buffer->getSampleRate() * 1000;
	if (bufferTime != ms) {
		bufferTime = ms;
		controls.lock()->setUpdateTime(ms);
	}
}

void MeterProcess::detectOvers(int chan, vector<float>* samples, int len)
{
	auto overs = int(0);
	float sample;
	for (auto i = int(0); i < len; i++) {
		sample = (*samples)[i];
		if (sample > 1)
			overs++;
		else if (sample < -int(1))
			overs++;

	}
	if (overs > 0) {
		controls.lock()->addOvers(chan, overs);
	}
}

void MeterProcess::detectPeak(int chan, vector<float>* samples, int len)
{
	float peak = 0.0f;
	float sample;
	for (int i = 0; i < len; i++) {
		sample = (*samples)[i];
		if (sample > peak) {
			peak = sample;
		}
		else if (-sample > peak) {
			peak = -sample;
		}
	}
	//controls.lock()->setPeak(chan, peak);
}

void MeterProcess::detectAverage(int chan, vector<float>* samples, int len)
{
	auto sumOfSquares = 0.0f;
	float sample;
	for (int i = 0; i < len; i++) {
		sample = (*samples)[i];
		sumOfSquares += (sample * sample);
	}
	auto rms = static_cast<float>(1.41 * sqrt(sumOfSquares / len));
	controls.lock()->setAverage(chan, rms);
}
