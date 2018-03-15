#include <audio/mixer/AudioMixerStrip.hpp>

#include <audio/core/MetaInfo.hpp>
#include <audio/core/AudioBuffer.hpp>
#include <audio/core/AudioControls.hpp>
#include <audio/core/AudioControlsChain.hpp>
#include <audio/core/AudioProcess.hpp>
#include <audio/core/ChannelFormat.hpp>
#include <audio/mixer/AudioMixer.hpp>
#include <audio/mixer/AudioMixerBus.hpp>
#include <audio/mixer/MainMixProcess.hpp>
#include <audio/mixer/MixVariables.hpp>
#include <audio/mixer/MixerControlsIds.hpp>

using namespace ctoot::audio::mixer;
using namespace ctoot::audio::core;
using namespace std;

AudioMixerStrip::AudioMixerStrip(AudioMixer* mixer, weak_ptr<AudioControlsChain> controlsChain)
	: AudioProcessChain(controlsChain)
{
	silenceCountdown = silenceCount;
	this->mixer = mixer;
	buffer = createBuffer();
	channelFormat = buffer->getChannelFormat();
}

weak_ptr<AudioProcess> AudioMixerStrip::getInputProcess()
{
    return input;
}

void AudioMixerStrip::setInputProcess(weak_ptr<AudioProcess> input)
{

	if (controlChain.lock()->getId() != MixerControlsIds::CHANNEL_STRIP) {
		MLOG("No external input to this strip type");
		return;
	}
	auto oldInput = this->input;
	if (input.lock()) input.lock()->open();

	this->input = input;
	if (!input.lock()) {
		this->metaInfo.reset();
		controlChain.lock()->setMetaInfo(weak_ptr<MetaInfo>());
	}
	if (oldInput.lock())
		oldInput.lock()->close();
}

weak_ptr<AudioProcess> AudioMixerStrip::getDirectOutputProcess()
{
    return directOutput;
}

void AudioMixerStrip::setDirectOutputProcess(weak_ptr<AudioProcess> output)
{
	auto oldOutput = directOutput;
	if (output.lock()) output.lock()->open();

	this->directOutput = output;
	if (oldOutput.lock()) oldOutput.lock()->close();
}

void AudioMixerStrip::silence()
{
	if (nmixed > 0) {
		buffer->makeSilence();
		nmixed = 0;
	}
}

AudioBuffer* AudioMixerStrip::createBuffer()
{
	auto id = controlChain.lock()->getId();
	if (id == MixerControlsIds::CHANNEL_STRIP) {
		isChannel = true;
		return mixer->getSharedBuffer();
	}
	else if (id == MixerControlsIds::GROUP_STRIP) {
		auto buf = mixer->createBuffer(getName());
		buf->setChannelFormat(mixer->getMainBus()->getBuffer()->getChannelFormat());
		return buf;
	}
	else if (id == MixerControlsIds::MAIN_STRIP) {
		return mixer->getMainBus()->getBuffer();
	}
	return mixer->getBus(getName())->getBuffer();
}

const int AudioMixerStrip::silenceCount;

bool AudioMixerStrip::processBuffer()
{
	auto ret = AUDIO_OK;
	if (isChannel) {
		if (input.lock()) {
			ret = input.lock()->processAudio(buffer);
			buffer->getMetaInfo();
			checkMetaInfo(buffer->getMetaInfo());
			if (ret == AUDIO_DISCONNECT) {
				processMutations();
				return false;
			}
			else if (ret == AUDIO_SILENCE && silenceCountdown == 0) {
				return false;
			}
		}
		else {
			processMutations();
			return false;
		}
	}
	processAudio(buffer);
	if (isChannel) {
		if (ret == AUDIO_SILENCE) {
			if (buffer->square() > 0.00000001f)
				silenceCountdown = silenceCount;
			else
				silenceCountdown--;
		}
		else {
			silenceCountdown = silenceCount;
		}
	}
	if (directOutput.lock()) {
		directOutput.lock()->processAudio(buffer);
	}
	return true;
}

void AudioMixerStrip::checkMetaInfo(weak_ptr<MetaInfo> wInfo)
{
	auto info = wInfo.lock();
	//metaInfo.reset();
	//metaInfo = make_shared<MetaInfo>(info->getSourceLabel(), info->getSourceLocation());
	//controlChain->setMetaInfo(metaInfo);
}

shared_ptr<AudioProcess> AudioMixerStrip::createProcess(weak_ptr<AudioControls> controls)
{
	auto candidate = dynamic_pointer_cast<MixVariables>(controls.lock());
	if (candidate) {
		weak_ptr<AudioMixerStrip> routedStrip;
		if (candidate->getName().compare(mixer->getMainBus()->getName()) == 0) {
			routedStrip = mixer->getMainStrip();
			try {
				return make_shared<MainMixProcess>(routedStrip.lock(), candidate, mixer);
			}
			catch (bad_cast e) {
				printf("\n%s", e.what());
			}
		}
		else {
			routedStrip = mixer->getStripImpl(candidate->getName());
			return make_shared<MixProcess>(routedStrip.lock(), candidate);
		}
	}
	return AudioProcessChain::createProcess(controls);
}

int AudioMixerStrip::mix(ctoot::audio::core::AudioBuffer* bufferToMix, vector<float> gain)
{
	if (bufferToMix == nullptr) return 0;
	auto ret = channelFormat.lock()->mix(buffer, bufferToMix, gain);
	if (ret != 0) nmixed += 1;
	return ret;
}

void AudioMixerStrip::close()
{
    AudioProcessChain::close();
    mixer->removeBuffer(buffer);
}

AudioMixerStrip::~AudioMixerStrip() {
}
