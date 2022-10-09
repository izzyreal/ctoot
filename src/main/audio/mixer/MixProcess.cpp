#include <audio/mixer/MixProcess.hpp>
#include <audio/mixer/AudioMixerStrip.hpp>

#include <Logger.hpp>

using namespace ctoot::audio::mixer;
using namespace ctoot::audio::core;
using namespace std;

MixProcess::MixProcess(weak_ptr<AudioMixerStrip> strip, weak_ptr<MixVariables> vars)
{
	if (!strip.lock()) {
		return;
	}
	routedStrip = strip;
	this->vars = vars;
	auto format = vars.lock()->getChannelFormat();
	smoothingFactor = vars.lock()->getSmoothingFactor();
	channelGains = vector<float>(format->getCount());
	smoothedChannelGains = vector<float>(format->getCount());
}

AudioMixerStrip* MixProcess::getRoutedStrip()
{
    return routedStrip.lock().get();
}

int MixProcess::processAudio(AudioBuffer* buffer)
{
    auto lVars = vars.lock();
	if (!lVars->isEnabled() && lVars->isMaster()) {
		buffer->makeSilence();
	}
	else if (lVars->isEnabled()) {
//		gain = vars.lock()->getGain();
		//if (gain > 0.0f || vars->isMaster()) {
			lVars->getChannelGains(&channelGains);
			for (auto c = 0; c < channelGains.size(); c++) {
				smoothedChannelGains[c] += smoothingFactor * (channelGains[c] - smoothedChannelGains[c]);
			}
			getRoutedStrip()->mix(buffer, smoothedChannelGains);
		//}
	}
	return AUDIO_OK;
}

MixProcess::~MixProcess() {
}
