#include <audio/delay/MultiTapDelayControls.hpp>

#include <audio/delay/DelayTapControls.hpp>

using namespace ctoot::audio::delay;
using namespace ctoot::control;
using namespace std;

weak_ptr<ControlLaw> MultiTapDelayControls::LAW(float msMax) {
	static auto res = make_shared<LinearLaw>(0.1f, msMax, "ms");
	return res;
}

MultiTapDelayControls::MultiTapDelayControls(int idOffset, int ntaps, float msMax, std::string name)
	: AudioControls(idOffset, name)
{
    for (auto t = int(0); t < ntaps; t++) {
        auto controls = make_shared<DelayTapControls>(idOffset + t + t, LAW(msMax));
        add(controls);
        taps.push_back(controls);
    }
}

vector<weak_ptr<DelayTap>> MultiTapDelayControls::getTaps()
{
    return taps;
}

bool MultiTapDelayControls::isNeverBordered()
{
    return true;
}

/*
java::lang::String* MultiTapDelayControls::getAlternate()
{
    return u"Channel";
}
*/
