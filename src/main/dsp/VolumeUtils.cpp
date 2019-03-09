#include <dsp/VolumeUtils.hpp>

#include <cmath>

using namespace ctoot::dsp;

double VolumeUtils::FACTOR1 = 20.0 / log(10.0);

constexpr double VolumeUtils::FACTOR2;

double VolumeUtils::lin2log(double dLinear)
{
    return FACTOR1 * log(dLinear);
}

double VolumeUtils::log2lin(double dLogarithmic)
{
    return pow(10.0, dLogarithmic * FACTOR2);
}

double VolumeUtils::lin2log(double dLinear, double a, double b)
{
	return (a / log(b)) * log(dLinear);
}
