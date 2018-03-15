#include <dsp/Phasor.hpp>

#include <cmath>

using namespace ctoot::dsp;

Phasor::Phasor(double w, double theta)
{
	b1 = 2.0f * cos(w);
	y1 = sin(theta - w);
	y2 = sin(theta - 2 * w);
}

float Phasor::out()
{
    y0 = b1 * y1 - y2;
    y2 = y1;
    y1 = y0;
    return static_cast< float >(y0);
}
