#include <audio/delay/FrequencyModulationProcess.hpp>

#include <audio/core/AudioBuffer.hpp>
#include <audio/delay/DelayBuffer.hpp>
#include <audio/delay/DelayVariables.hpp>

using namespace ctoot::audio::delay;
using namespace std;

FrequencyModulationProcess::FrequencyModulationProcess(DelayVariables* vars)
{
	samples = vector<vector<float>*>(6);
	sampleRate = 0;
	this->vars = vars;
    wasBypassed = !vars->isBypassed();
    maxDelayMillis = vars->getMaxDelayMilliseconds();
}

void FrequencyModulationProcess::open()
{
}

void FrequencyModulationProcess::cacheProcessVariables()
{
}

void FrequencyModulationProcess::sampleRateChanged()
{
}

int FrequencyModulationProcess::processAudio(ctoot::audio::core::AudioBuffer* buffer)
{
	auto bypassed = vars->isBypassed();
	if (bypassed) {
		if (!wasBypassed) {
			if (delayBuffer != nullptr)
				delayBuffer->makeSilence();

			wasBypassed = true;
		}
		return AUDIO_OK;
	}
	wasBypassed = bypassed;
	auto sr = static_cast<int>(buffer->getSampleRate());
	if (sampleRate != sr) {
		sampleRate = sr;
		delayBuffer = new DelayBuffer(buffer->getChannelCount(), msToSamples(maxDelayMillis, sampleRate), sampleRate);
		staticDelay = static_cast<int>((delayBuffer->msToSamples(maxDelayMillis / 2.0f)));
		sampleRateChanged();
	}
	delayBuffer->conform(buffer);
	cacheProcessVariables();
	auto ns = buffer->getSampleCount();
	auto nc = buffer->getChannelCount();
	for (auto c = int(0); c < nc; c++) {
		samples[c] = buffer->getChannel(c);
	}
	for (auto s = int(0); s < ns; s++) {
		auto delay = staticDelay * (1.0f + modulation());
		for (auto ch = int(0); ch < nc; ch++) {
			delayBuffer->append(ch, (*samples[ch])[s]);
			(*samples[ch])[s] = delayBuffer->outA(ch, delay);
		}
		delayBuffer->nudge(1);
	}
	return AUDIO_OK;
}

void FrequencyModulationProcess::close()
{
    delayBuffer = nullptr;
}

int FrequencyModulationProcess::msToSamples(float ms, float sr)
{
    return round((ms * sr) / int(1000));
}
