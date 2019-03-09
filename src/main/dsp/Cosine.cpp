#include <dsp/Cosine.hpp>

#define _USE_MATH_DEFINES
#include <math.h>

using namespace ctoot::dsp;

Cosine::Cosine(double w)
	: Phasor(w, 0.5 * M_PI)
{
}
