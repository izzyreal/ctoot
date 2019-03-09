#include <audio/core/ControlChainObserver.hpp>
#include <audio/core/AudioProcessChain.hpp>
#include <observer/Observable.hpp>
#include <control/ChainMutation.hpp>

#include <stdio.h>

using namespace ctoot::audio::core;
using namespace ctoot::control;

ControlChainObserver::ControlChainObserver(AudioProcessChain* apc) {
	this->apc = apc;
}

void ControlChainObserver::update(moduru::observer::Observable* o, std::any arg)
{
	ChainMutation* candidate = nullptr;
	try {
		candidate = std::any_cast<ChainMutation*>(arg);
	}
	catch (const std::bad_any_cast& e) {
		printf(e.what());
		return;
	}
	apc->mutationQueue.try_enqueue(candidate);
}

ControlChainObserver::~ControlChainObserver() {
}
