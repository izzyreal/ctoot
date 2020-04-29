#include <audio/basic/tap/TapProcess.hpp>

#include <audio/basic/tap/TapControls.hpp>
#include <audio/core/AudioBuffer.hpp>

#include <VecUtil.hpp>

using namespace ctoot::audio::basic::tap;

TapProcess::TapProcess(TapControls* controls)
{
    this->controls = controls;
}

void TapProcess::open()
{
    tap = controls->getBuffer();
}

int32_t TapProcess::processAudio(ctoot::audio::core::AudioBuffer* buffer)
{
	//MLOG("TapProcess::processAudio");
	if (controls->isInactive()) {
		//MLOG("TapProcess is inactive");
		return AUDIO_OK;
	}

	tap->setChannelFormat(buffer->getChannelFormat());
	auto ns = buffer->getSampleCount();
	auto nc = buffer->getChannelCount();
	for (auto i = int32_t(0); i < nc; i++) {
		moduru::VecUtil::VecCopy(buffer->getChannel(i), 0, tap->getChannel(i), 0, ns);
	}
	return AUDIO_OK;
}

void TapProcess::close()
{
    controls->removeBuffer();
}
