#include "MindBControl.hpp"

#include <audio/meter/MeterControls.hpp>

using namespace ctoot::audio::meter;
using namespace std;

MindBControl::MindBControl()
	: ctoot::control::EnumControl(MeterControls::METER_MIN_DB, "Min", float(-60))
{
    values.push_back(float(-12));
    values.push_back(float(-20));
    values.push_back(float(-40));
    values.push_back(float(-60));
    values.push_back(float(-80));
    values.push_back(float(-100));
    values.push_back(float(-120));
	floatValues = vector<float>(values.size());
    for (int i = 0; i < values.size(); i++) {
		floatValues[i] = nonstd::any_cast<float>(values[i]);
    }
}

vector<nonstd::any> MindBControl::getValues()
{
    return values;
}

float ctoot::audio::meter::MindBControl::getMindB()
{
	for (int j = 0; j < values.size(); j++) {
		if (nonstd::any_cast<float>(values[j]) == nonstd::any_cast<float>(getValue())) return floatValues[j];
	}
	return {};
}

int32_t ctoot::audio::meter::MindBControl::getWidthLimit()
{
    return 127;
}
