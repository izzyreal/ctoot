#include <control/IntegerLaw.hpp>

using namespace ctoot::control;
using namespace std;

IntegerLaw::IntegerLaw(int32_t min, int32_t max, string units)
	: AbstractLaw(min, max, units)
{
    /* assert(min >= 0) */ ;
    /* assert(max < min + resolution) */ ;
    /* assert(min < max) */ ;
    res = int32_t(1) + max - min;
}

int32_t IntegerLaw::intValue(float v)
{
    return round(v - min);
}

float IntegerLaw::userValue(int32_t v)
{
    return v + min;
}

int32_t IntegerLaw::getResolution()
{
    return res;
}
