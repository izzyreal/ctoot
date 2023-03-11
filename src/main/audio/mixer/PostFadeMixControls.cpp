#include <audio/mixer/PostFadeMixControls.hpp>
#include <audio/mixer/MainMixControls.hpp>

using namespace std;
using namespace ctoot::audio::mixer;

PostFadeMixControls::PostFadeMixControls(MixerControls* mixerControls, int stripId, weak_ptr<BusControls> busControls, MainMixControls* mainMixControls)
	: MixControls(mixerControls, stripId, busControls.lock(), false)
{
	this->mainMixControls = mainMixControls;
}

float PostFadeMixControls::getGain()
{
    return MixControls::getGain() * mainMixControls->getGain();
}

PostFadeMixControls::~PostFadeMixControls() {
	mainMixControls = nullptr;
}
