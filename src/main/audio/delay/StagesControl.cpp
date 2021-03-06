#include <audio/delay/StagesControl.hpp>

#include <audio/delay/PhaserControls.hpp>

using namespace ctoot::audio::delay;
using namespace ctoot::control;
using namespace std;

std::vector<std::string> StagesControl::values{ "2", "4", "6", "8", "10", "12" };

StagesControl::StagesControl(int stages)
	: EnumControl(PhaserControls::STAGES_ID, "Stages", to_string(stages))
{
}

vector<nonstd::any> StagesControl::getValues()
{
	vector<nonstd::any> res;
	for (auto& s : values)
		res.push_back(s);
	return res;
}

int StagesControl::getStages()
{
    return stoi(nonstd::any_cast<string>(getValue()));
}
