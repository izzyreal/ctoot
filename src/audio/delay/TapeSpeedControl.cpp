#include <audio/delay/TapeSpeedControl.hpp>

#include <audio/delay/WowFlutterControls.hpp>

using namespace ctoot::audio::delay;
using namespace std;

TapeSpeedControl::TapeSpeedControl(WowFlutterControls *WowFlutterControls_this)
	: EnumControl(WowFlutterControls::SPEED, "ips", string("15"))
    , WowFlutterControls_this(WowFlutterControls_this)
{
}

vector<boost::any> TapeSpeedControl::getValues()
{
	vector<boost::any> res;
	for (auto& s : WowFlutterControls::speeds())
		res.push_back(s);
	return res;
}

bool TapeSpeedControl::hasLabel()
{
    return true;
}
