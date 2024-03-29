#include <control/LogLaw.hpp>

#include <control/ControlLaw.hpp>

//#include <Logger.hpp>

#include <cassert>
#include <cmath>

using namespace ctoot::control;
using namespace std;

LogLaw::LogLaw(float min, float max, string units) : AbstractLaw(min, max, units)
{
    assert(min != 0.f);
	assert(max != 0.f);
	logMin = log10(min);
	logMax = log10(max);
	logSpan = logMax - logMin;
}

int LogLaw::intValue(float userVal)
{
	if (userVal == 0) userVal = 1;
	return static_cast<int>(0.5f + ((resolution - 1) * (log10(userVal) - logMin) / logSpan));
}

float LogLaw::userValue(int intVal)
{
    auto p = logMin + (logSpan * intVal) / (resolution - 1);
    return static_cast< float >(pow(10, p));
}
