#include <audio/delay/TapeSpeedControl.hpp>

#include <audio/delay/WowFlutterControls.hpp>

using namespace ctoot::audio::delay;
using namespace std;

TapeSpeedControl::TapeSpeedControl(WowFlutterControls *WowFlutterControls_this)
	: EnumControl(WowFlutterControls::SPEED, "ips", string("15"))
    , WowFlutterControls_this(WowFlutterControls_this)
{
}

vector<nonstd::any> TapeSpeedControl::getValues()
{
	vector<nonstd::any> res;
	for (auto& s : WowFlutterControls::speeds())
		res.push_back(s);
	return res;
}

bool TapeSpeedControl::hasLabel()
{
    return true;
}
