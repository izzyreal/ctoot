#include <audio/core/ControlChainObserver.hpp>
#include <audio/core/AudioProcessChain.hpp>
#include <observer/Observable.hpp>
#include <control/ChainMutation.hpp>

#include <Logger.hpp>

using namespace ctoot::audio::core;

ControlChainObserver::ControlChainObserver(AudioProcessChain* apc) {
	this->apc = apc;
}

void ControlChainObserver::update(moduru::observer::Observable* o, boost::any arg)
{
	ctoot::control::ChainMutation* candidate = nullptr;
	try {
		candidate = boost::any_cast<ctoot::control::ChainMutation*>(arg);
	}
	catch (boost::bad_any_cast e) {
		std::string msg = e.what();
		//MLOG("Couldn't cast to chain mutation " + msg);
		return;
	}
	apc->mutationQueue.try_enqueue(candidate);
}

ControlChainObserver::~ControlChainObserver() {
	apc = nullptr;
}
