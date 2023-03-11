#include "AudioProcessChain.hpp"

#include <audio/core/AudioControls.hpp>
#include <audio/core/AudioControlsChain.hpp>
#include <audio/core/AudioProcess.hpp>
#include <audio/core/AudioServices.hpp>

using namespace std;
using namespace ctoot::control;
using namespace ctoot::audio::core;

AudioProcessChain::AudioProcessChain(weak_ptr<AudioControlsChain> controlChain)
{
	this->controlChain = controlChain;
}

void AudioProcessChain::open()
{
	for (auto& control : controlChain.lock()->getControls()) {

		auto candidate = dynamic_pointer_cast<AudioControls>(control.lock());

		if (candidate) {
			auto p = createProcess(candidate);
			if (p != nullptr) {
                processes.push_back(p);
				p->open();
			}
		}
	}
}

int AudioProcessChain::processAudio(ctoot::audio::core::AudioBuffer* buffer, int nFrames)
{
	for (auto& p : processes) {
		try {
			if (p) {
				p->processAudio(buffer, nFrames);
			}
		}
		catch (const exception& e) {
			try {
				p->close();
			}
			catch (const exception& e2) {
				e2.what();
			}
			p.reset();
			string error = "DISABLED AudioProcess in " + getName() + " due to: " + e.what();
		}
	}
	return AUDIO_OK;
}

void AudioProcessChain::close()
{
	for (auto& p : processes) {
		if (!p) continue;
		p->close();
	}
	processes.clear();
}

string AudioProcessChain::getName()
{
    return controlChain.lock()->getName();
}

shared_ptr<AudioProcess> AudioProcessChain::createProcess(weak_ptr<AudioControls> controls)
{
    return AudioServices::createProcess(controls);
}
