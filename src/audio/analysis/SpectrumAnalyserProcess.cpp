#include "SpectrumAnalyserProcess.hpp"

#include "SpectrumAnalyserControls.hpp"

#define _USE_MATH_DEFINES
#include <math.h>

using namespace ctoot::audio::analysis;
using namespace ctoot::audio::core;
using namespace ctoot::control;
using namespace std;

SpectrumAnalyserProcess::SpectrumAnalyserProcess(weak_ptr<SpectrumAnalyserControls> controls)
{
	this->controls = controls;
	circBuf = make_unique<moduru::io::StereoCircularTBuffer>(48000);
	fft = make_unique<FFTReal>(FFT_SIZE);
	controls.lock()->setValues(vector<float>(FFT_SIZE/2));
}

SpectrumAnalyserProcess::~SpectrumAnalyserProcess()
{
}


// Hann
void applyWindow(vector<float>& data) {
	auto ns = data.size();
	for (int i = 0; i < ns; i++) {
		double multiplier = 0.5 * (1.0 - cos(2.0 * M_PI * i / (ns - 1.0)));
		data[i] = multiplier * data[i];
	}
}

/*
// 4-term Blackman-Harris
void applyWindow(vector<float>& samples)
{
	auto numSamples = samples.size();
	const float a0 = 0.35875f;
	const float a1 = 0.48829f;
	const float a2 = 0.14128f;
	const float a3 = 0.01168f;

	const double oneOverSize = (1.0 / numSamples);
	const double oneOverSizeMinusOne = 1.0 / (numSamples - 1.0);
	float windowFactor = 0.0f;

	for (int i = 0; i < numSamples; i++)
	{
		// Blackman-Harris window equation
		float window = a0 - a1 * (float)(std::cos((M_PI * 2) * i * oneOverSizeMinusOne))
			+ a2 * (float)(std::cos((M_PI * 4) * i * oneOverSizeMinusOne))
			- a3 * (float)(std::cos((M_PI * 6) * i * oneOverSizeMinusOne));
		samples[i] *= window;
		windowFactor += window;
	}
}
*/

int SpectrumAnalyserProcess::processAudio(AudioBuffer* buffer) {

	auto c = controls.lock();

	if (c->isBypassed()) {
		return AUDIO_OK;
	}

	if (sampleRate != buffer->getSampleRate()) {
		this->sampleRate = buffer->getSampleRate();
		c->setSampleRate(buffer->getSampleRate());
	}

	const int ns = buffer->getSampleCount();
	auto l = *buffer->getChannel(0);
	auto r = *buffer->getChannel(1);
	circBuf->write(&l, &r, ns);

	vector<float> l1(FFT_SIZE);
	vector<float> r1(FFT_SIZE);
	vector<float> resultL(FFT_SIZE);
	vector<float> resultR(FFT_SIZE);

	circBuf->read(&l1, &r1, -FFT_SIZE, FFT_SIZE);
	circBuf->moveReadPos(ns);

	applyWindow(l1);
	applyWindow(r1);

	fft->do_fft(&resultL[0], &l1[0]);
	fft->do_fft(&resultR[0], &r1[0]);

	int vCounter = 0;
	for (int i = 0; i <= FFT_SIZE / 2; i++)
	{
		double img;

		const double real = resultL[i];
		if (i > 0 && i < FFT_SIZE / 2) {
			img = resultL[i + FFT_SIZE / 2];
		}
		else {
			img = 0;
		}

		const double f_abs = sqrt(real * real + img * img);
		float v = abs(f_abs / (FFT_SIZE / 2));
		c->setValue(vCounter++, v);
	}

	return AUDIO_OK;
}
