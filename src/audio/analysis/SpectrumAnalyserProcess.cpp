#include "SpectrumAnalyserProcess.hpp"

#include "SpectrumAnalyserControl.hpp"

using namespace ctoot::audio::analysis;
using namespace ctoot::audio::core;
using namespace ctoot::control;
using namespace std;

SpectrumAnalyserProcess::SpectrumAnalyserProcess(weak_ptr<SpectrumAnalyserControl> control)
{
	this->control = control;
}

SpectrumAnalyserProcess::~SpectrumAnalyserProcess()
{
}

int SpectrumAnalyserProcess::processAudio(AudioBuffer* buffer) {

	const int ns = buffer->getSampleCount();
	auto l = buffer->getChannel(0);
	auto r = buffer->getChannel(1);

	for (int i = 0; i < ns; i++) {

		auto lSample = (*l)[i];
		auto rSample = (*r)[i];

	}
	return AUDIO_OK;
}

int SpectrumAnalyserProcess::getBandCount() {
	return control.lock()->getValues()->size();
}
