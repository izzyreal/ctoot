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

void ControlChainObserver::update(moduru::observer::Observable* o, nonstd::any arg)
{
    if (arg.has_value() && arg.type() == typeid(ChainMutation*))
    {
		auto mutation = nonstd::any_cast<ChainMutation*>(arg);
        apc->mutationQueue.try_enqueue(mutation);
	}
}

ControlChainObserver::~ControlChainObserver() {
}
