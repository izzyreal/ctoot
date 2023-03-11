#include "AudioProcessChain.hpp"

#include <audio/core/AudioControls.hpp>
#include <audio/core/AudioControlsChain.hpp>
#include <audio/core/AudioProcess.hpp>
#include <audio/core/ControlChainObserver.hpp>
#include <audio/core/AudioServices.hpp>
#include <control/ChainMutation.hpp>

#include <chrono>

using namespace std;
using namespace ctoot::control;
using namespace ctoot::audio::core;

AudioProcessChain::AudioProcessChain(weak_ptr<AudioControlsChain> controlChain)
{
	this->controlChain = controlChain;
	controlChainObserver = new ControlChainObserver(this);
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
	controlChain.lock()->addObserver(controlChainObserver);
}

int AudioProcessChain::processAudio(ctoot::audio::core::AudioBuffer* buffer, int nFrames)
{
	processMutations();

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
	controlChain.lock()->deleteObserver(controlChainObserver);
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

void AudioProcessChain::processMutations()
{
	ChainMutation* m = nullptr;
    
	if (!mutationQueue.try_dequeue(m)) return;

	switch (m->getType()) {

	case ChainMutation::DELETE:
	{
		auto p = dynamic_pointer_cast<AudioProcess>(processes[m->getIndex0()]);
		p->close();
		for (int i = 0; i < processes.size(); i++) {
			if (processes[i] == p) {
				processes.erase(processes.begin() + i);
				break;
			}
		}
		break;
	}
	case ChainMutation::INSERT:
	{
		auto controls = dynamic_cast<InsertMutation*>(m)->getControl().lock();
		auto candidate = dynamic_pointer_cast<AudioControls>(controls);
		if (candidate) {
			auto p = createProcess(candidate);
			processes.insert(processes.begin() + m->getIndex0(), p);
			if (p) {
				p->open();
			}
		}
		break;
	}
	case ChainMutation::MOVE:
	{
		std::shared_ptr<AudioProcess> process;
		process = dynamic_pointer_cast<AudioProcess>(processes[m->getIndex0()]);
		processes.erase(processes.begin() + m->getIndex0());
		processes.insert(processes.begin() + m->getIndex1(), process);
		break;
	}
	}
	delete m;
}

AudioProcessChain::~AudioProcessChain() {
	if (controlChainObserver != nullptr) {
		delete controlChainObserver;
		controlChainObserver = nullptr;
	}
}
