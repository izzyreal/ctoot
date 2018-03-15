#include <audio/mixer/PostFadeMixControls.hpp>
#include <audio/mixer/MainMixControls.hpp>

using namespace std;
using namespace ctoot::audio::mixer;

PostFadeMixControls::PostFadeMixControls(MixerControls* mixerControls, int stripId, weak_ptr<BusControls> busControls, MainMixControls* mainMixControls)
	: MixControls(mixerControls, stripId, busControls, false)
{
	this->mainMixControls = mainMixControls;
}

bool PostFadeMixControls::isEnabled()
{
    return MixControls::isEnabled() && !mainMixControls->isMute();
}

float PostFadeMixControls::getGain()
{
    return MixControls::getGain() * mainMixControls->getGain();
}

PostFadeMixControls::~PostFadeMixControls() {
	mainMixControls = nullptr;
}
