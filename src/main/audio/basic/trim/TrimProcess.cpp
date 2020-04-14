#include "TrimProcess.hpp"

using namespace ctoot::audio::basic::trim;

using namespace std;

TrimProcess::TrimProcess(weak_ptr<TrimControls> controls)
{
	this->controls = controls;
}

int TrimProcess::processAudio(AudioBuffer* buffer)
{
	auto c = controls.lock();
	
	if (c->isBypassed()) {
		return AUDIO_OK;
	}

	float trim = c->getTrim();

	int channelCount = buffer->getChannelCount();
	int sampleCount = buffer->getSampleCount();

	for (int c = 0; c < channelCount; c++) {
		auto samples = buffer->getChannel(c);
		for (int s = 0; s < sampleCount; s++) {
			(*samples)[s] *= trim;
		}
	}

	return AUDIO_OK;
}
		
TrimProcess::~TrimProcess()
{

}