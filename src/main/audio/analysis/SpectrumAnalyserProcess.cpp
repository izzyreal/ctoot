#include "SpectrumAnalyserProcess.hpp"

#include "SpectrumAnalyserControls.hpp"

#define _USE_MATH_DEFINES
#include <math.h>

using namespace ctoot::audio::analysis;
using namespace ctoot::audio::core;
using namespace ctoot::control;
using namespace std;

const int SpectrumAnalyserProcess::FFT_SIZE;

SpectrumAnalyserProcess::SpectrumAnalyserProcess(weak_ptr<SpectrumAnalyserControls> controls)
{
	this->controls = controls;
	circBuf = make_unique<moduru::io::StereoCircularTBuffer>(48000);
	fft = make_unique<FFTReal>(FFT_SIZE);
	controls.lock()->setValues(vector<float>(FFT_SIZE * 0.5));
}

SpectrumAnalyserProcess::~SpectrumAnalyserProcess()
{
}


// Hann
void applyWindow(vector<float>& data) {
	auto ns = data.size();
	for (int i = 0; i < ns; i++) {
		double multiplier = 0.5 * (1.0 - cos(2.0 * M_PI * i / (ns - 1.0)));
		data[i] = static_cast<float>(multiplier * data[i]);
	}
}

int SpectrumAnalyserProcess::processAudio(AudioBuffer* buffer) {
	auto c = controls.lock();

	if (c->isBypassed()) {
		return AUDIO_OK;
	}

	if (sampleRate != buffer->getSampleRate()) {
		this->sampleRate = static_cast<int>(buffer->getSampleRate());
		c->setSampleRate(buffer->getSampleRate());
	}

	const int ns = buffer->getSampleCount();

	circBuf->write(buffer->getChannel(0), buffer->getChannel(1), ns);

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
		if (i > 0 && i < FFT_SIZE * 0.5) {
			img = resultL[i + FFT_SIZE * 0.5];
		}
		else {
			img = 0;
		}

		const double f_abs = sqrt(real * real + img * img);
		float v = static_cast<float>(abs(f_abs / (FFT_SIZE * 0.5)));
		c->setValue(vCounter++, v);

	}

	return AUDIO_OK;
}
