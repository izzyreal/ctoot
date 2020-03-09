#include <audio/delay/CabMicingNControl.hpp>

#include <audio/delay/CabMicingControls.hpp>


using namespace ctoot::audio::delay;
using namespace ctoot::control;
using namespace std;

std::vector<std::string> CabMicingNControl::values;

CabMicingNControl::CabMicingNControl()
	: EnumControl(CabMicingControls::N_ID, "", "4x")
{
	values.push_back("2x");
	values.push_back("4x");
}

vector<nonstd::any> CabMicingNControl::getValues()
{
	vector<nonstd::any> res;
	for (auto& v : values)
		res.push_back(v);
	return res;
}
