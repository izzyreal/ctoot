#include "ResetControl.hpp"

#include <audio/meter/MeterControls.hpp>

using namespace ctoot::audio::meter;

ResetControl::ResetControl(MeterControls* mcThis)
	: ctoot::control::BooleanControl(MeterControls::METER_RESET, "Reset", false, true)
{
	this->mcThis = mcThis;
}

int32_t ctoot::audio::meter::ResetControl::getWidthLimit()
{
    return 127;
}
