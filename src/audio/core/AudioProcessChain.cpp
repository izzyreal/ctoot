#include "AudioProcessChain.hpp"

#include <audio/core/AudioControls.hpp>
#include <audio/core/AudioControlsChain.hpp>
#include <audio/core/AudioProcess.hpp>
#include <audio/core/ControlChainObserver.hpp>
#include <audio/core/AudioServices.hpp>
#include <control/ChainMutation.hpp>
#include <control/Control.hpp>

#include <chrono>

using namespace std;
using namespace ctoot::control;
using namespace ctoot::audio::core;

AudioProcessChain::AudioProcessChain(weak_ptr<AudioControlsChain> controlChain)
{
	this->controlChain = controlChain;
	debugTimes = false;
	debugIndex = 0;
	prevNanos = 0;
	controlChainObserver = new ControlChainObserver(this);
}

void AudioProcessChain::open()
{
	for (auto& control : controlChain.lock()->getControls()) {
		//MLOG("AudioProcessChain open iterating through controls. Current control: " + control->getName());
		auto candidate = dynamic_pointer_cast<AudioControls>(control.lock());
		if (candidate) {
			auto p = createProcess(candidate);
			if (p != nullptr) {
				//MLOG("Valid process created from control " + control->getName());
				processes.push_back(p);
				p->open();
			}
			else {
				MLOG("No process created from control " + candidate->getName());
			}
		}
	}
	controlChain.lock()->addObserver(controlChainObserver);
	if (debugTimes) {
		t.clear();
	}
}

int AudioProcessChain::processAudio(ctoot::audio::core::AudioBuffer* buffer)
{
	processMutations();
	if (debugTimes) {
		tstart = chrono::high_resolution_clock::now().time_since_epoch().count();
		elapsed = tstart - prevNanos;
		prevNanos = tstart;
		debugIndex += 1;
		debugIndex %= 100;
		if (debugIndex == 0) {
			return debugProcessAudio(buffer);
		}
	}
	for (auto& p : processes) {
		try {
			if (p) {
				p->processAudio(buffer);
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

int AudioProcessChain::debugProcessAudio(ctoot::audio::core::AudioBuffer* buffer)
{
	auto len = processes.size();
	for (auto i = 0; i < len; i++) {
		processes[i]->processAudio(buffer);
		t[i] = chrono::high_resolution_clock::now().time_since_epoch().count();
	}
	auto load = static_cast<int>(100 * (t[len - 1] - tstart) / elapsed);
	//    npc(::java::lang::System::out())->print(stringBuilder().append(load)->append(u"%: "->toString());
	auto prevt = tstart;
	for (auto i = 0; i < len; i++) {
		///        npc(::java::lang::System::out())->print(stringBuilder().append(((*t)[i] - prevt))->append(u", "->toString());
		prevt = t[i];
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
	t.clear();
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
	mutationQueue.try_dequeue(m);
	if (m == nullptr) return;
	shared_ptr<AudioProcess> p;
	shared_ptr<Control> controls;
	switch (m->getType()) {
	case ChainMutation::DELETE:
	{
		p = dynamic_pointer_cast<AudioProcess>(processes[m->getIndex0()]);
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
		controls = dynamic_pointer_cast<Control>(controlChain.lock()->getControls()[m->getIndex0()].lock());
		auto candidate = dynamic_pointer_cast<AudioControls>(controls);
		if (candidate) {
			p = createProcess(candidate);
			processes.insert(processes.begin() + m->getIndex0(), p);
			if (p) {
				p->open();
				MLOG("Successfully inserted process based on control " + controls->getName());
			}
			else {
				MLOG("NOT successfully inserted process based on control " + controls->getName());
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
