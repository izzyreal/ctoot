#include <util/RouteObserver.hpp>
#include <string>

using namespace ctoot::util;
using namespace std;
using namespace ctoot::audio::mixer;

RouteObserver::RouteObserver(MainMixProcess* mmp, AudioMixer* mixer) : mmp(mmp), mixer(mixer) {
}

void RouteObserver::update(moduru::observer::Observable* o, nonstd::any a) {
	string value = mmp->routeControl->getValueString();
	mmp->nextRoutedStrip = mixer->getStripImpl(value);
}
