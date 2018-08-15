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
	circBuf = make_unique<moduru::io::StereoCircularTBuffer>(FFT_SIZE);
	fft = make_unique<FFTReal>(FFT_SIZE);
}

SpectrumAnalyserProcess::~SpectrumAnalyserProcess()
{
}

void applyWindow(vector<float>& data) {
	auto ns = data.size();
	for (int i = 0; i < ns; i++) {
		double multiplier = 0.5 * (1 - cos(2 * M_PI * i / (ns - 1)));
		data[i] = multiplier * data[i];
	}
}

int SpectrumAnalyserProcess::processAudio(AudioBuffer* buffer) {

	auto c = controls.lock();

	if (c->isBypassed()) {
		return AUDIO_OK;
	}

	if (sampleRate != buffer->getSampleRate()) {
		c->setValues(vector<float>(64));
	}

	const int ns = buffer->getSampleCount();
	auto l = *buffer->getChannel(0);
	auto r = *buffer->getChannel(1);

	//applyWindow(l);
	//applyWindow(r);

	int length = min(ns, FFT_SIZE);

	circBuf->write(&l, &r, length);
	
	vector<float> l1(FFT_SIZE);
	vector<float> r1(FFT_SIZE);
	vector<float> resultL(FFT_SIZE);
	vector<float> resultR(FFT_SIZE);

	circBuf->read(&l1, &r1, 0, FFT_SIZE);

	fft->do_fft(&resultL[0], &l1[0]);
	fft->do_fft(&resultR[0], &r1[0]);
	//fft->do_ifft(&resultL[0], &l1[0]);
	//fft->do_ifft(&resultR[0], &r1[0]);
	//fft->rescale(&l1[0]);
	//fft->rescale(&r1[0]);

	for (int i = 0; i < c->getValues()->size(); i++) {
		auto v = resultL[i * ((FFT_SIZE / 2) / c->getValues()->size())];
		c->setValue(i, v);
	}

	return AUDIO_OK;
}
