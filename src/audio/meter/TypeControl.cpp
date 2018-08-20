#include <audio/meter/TypeControl.hpp>

#include <audio/meter/MeterControls.hpp>

using namespace ctoot::audio::meter;
using namespace std;

TypeControl::TypeControl()
	: ctoot::control::EnumControl(MeterControls::METER_TYPE, "Type", string("K-20/RMS"))
{
	values.push_back(string("K-20/RMS"));
	values.push_back(string("K-14/RMS"));
	values.push_back(string("K-12/RMS"));
	floatValues = vector<float>(values.size());
	for (int i = 0; i < values.size(); i++) {
		floatValues[i] = stof(boost::any_cast<string>(values[i]).substr(2, 4));
	}
}

vector<boost::any> ctoot::audio::meter::TypeControl::getValues()
{
    return values;
}

float ctoot::audio::meter::TypeControl::getMaxdB()
{
	for (int j = 0; j < values.size(); j++) {
		if (boost::any_cast<string>(values[j]) == boost::any_cast<string>(getValue())) return floatValues[j];
	}
	return {};
}

int32_t ctoot::audio::meter::TypeControl::getWidthLimit()
{
    return 127;
}
