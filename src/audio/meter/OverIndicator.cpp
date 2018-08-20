#include "OverIndicator.hpp"

#include <audio/meter/MeterControls.hpp>

using namespace ctoot::audio::meter;

OverIndicator::OverIndicator()
	: ctoot::control::Control(MeterControls::METER_OVERS, "")
{
}
