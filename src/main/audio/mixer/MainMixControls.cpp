#include <audio/mixer/MainMixControls.hpp>
#include <audio/mixer/RouteControl.hpp>
#include <audio/mixer/MixerControls.hpp>
#include <audio/mixer/MixerControlsIds.hpp>
#include <control/Control.hpp>
#include <control/EnumControl.hpp>

using namespace ctoot::audio::mixer;
using namespace std;

MainMixControls::MainMixControls(MixerControls* mixerControls, int stripId, weak_ptr<BusControls> busControls, bool isMaster) 
	: MixControls(mixerControls, stripId, busControls, isMaster)
{
}

ctoot::control::EnumControl* MainMixControls::createRouteControl(int stripId)
{
	if (stripId != MixerControlsIds::MAIN_STRIP && stripId != MixerControlsIds::AUX_STRIP) {
		auto controls = mixerControls->getControls();
		auto c = controls[0].lock();
		routeControl = new RouteControl(this, c->getName(), stripId == MixerControlsIds::CHANNEL_STRIP);
		return routeControl;
	}
	return nullptr;
}

ctoot::control::EnumControl* MainMixControls::getRouteControl()
{
    return routeControl;
}

MainMixControls::~MainMixControls() {
}