#include <audio/mixer/FxBusMasterMixControls.hpp>

using namespace std;
using namespace ctoot::audio::mixer;

FxBusMasterMixControls::FxBusMasterMixControls(bool hasMixControls, MixerControls* mixerControls, int stripId, weak_ptr<BusControls> busControls, bool isMaster)
	: MixControls(mixerControls, stripId, busControls.lock(), isMaster)
{
	this->hasMixControls = hasMixControls;
}

bool FxBusMasterMixControls::canBeInsertedBefore()
{
    return !hasMixControls;
}

bool FxBusMasterMixControls::canBeMovedBefore()
{
    return !hasMixControls;
}

bool FxBusMasterMixControls::canBeMoved()
{
    return !hasMixControls;
}
