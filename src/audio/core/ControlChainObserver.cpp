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
	//MLOG("ControlChainObserver update");
	try {
		boost::any_cast<ctoot::control::ChainMutation*>(arg);
	}
	catch (boost::bad_any_cast e) {
		std::string msg = e.what();
		//MLOG("Couldn't cast to chain mutation " + msg);
		return;
	}
	auto candidate = boost::any_cast<ctoot::control::ChainMutation*>(arg);
	apc->mutationQueue.try_enqueue(candidate);
	apc->processMutations();
}

ControlChainObserver::~ControlChainObserver() {
	apc = nullptr;
}
