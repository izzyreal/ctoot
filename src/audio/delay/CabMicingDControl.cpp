#include <audio/delay/CabMicingDControl.hpp>

#include <audio/delay/CabMicingControls.hpp>

using namespace ctoot::audio::delay;
using namespace ctoot::control;
using namespace std;

CabMicingDControl::CabMicingDControl()
	: EnumControl(CabMicingControls::D_ID, "", "12\"")
{
}
vector<string> CabMicingDControl::values{ "8\"", "10\"","12\"","15\"","18\"" };

vector<boost::any> CabMicingDControl::getValues()
{
	vector<boost::any> res;
	for (auto& v : values)
		res.push_back(v);
	return res;
}
