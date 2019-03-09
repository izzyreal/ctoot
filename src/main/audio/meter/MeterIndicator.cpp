#include <audio/meter/MeterIndicator.hpp>

#include <audio/meter/MeterControls.hpp>
#include <control/LinearLaw.hpp>

using namespace ctoot::audio::meter;
using namespace std;

MeterIndicator::MeterIndicator(string name)
	: ctoot::control::FloatControl(MeterControls::METER_INDICATOR, name, MeterControls::METER_LAW(), 0.5f, -60.0f)
{
    indicator = true;
}
