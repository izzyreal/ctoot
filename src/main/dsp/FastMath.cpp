#include "FastMath.hpp"

#include <cmath>

#define _USE_MATH_DEFINES
#include <math.h>  

using namespace ctoot::dsp;

constexpr float FastMath::S_B;
constexpr float FastMath::S_C;

float FastMath::sin(float x)
{
    return S_B * x + S_C * x * abs(x);
}

constexpr float FastMath::TWODIVPI;

float FastMath::triangle(float x)
{
    x += M_PI;
    x *= TWODIVPI;
    x -= 1;
    if(x > 1)
        x -= 4.0f;

    return abs(-(abs(x) - 2.0f)) - 1.0f;
}

float FastMath::min(float a, float b)
{
    return a < b ? a : b;
}

float FastMath::max(float a, float b)
{
    return a > b ? a : b;
}

/*
double FastMath::sqrt(double a)
{
    return ::java::lang::Double::longBitsToDouble(((::java::lang::Double::doubleToLongBits(a) >> int32_t(32)) + int32_t(1072632448)) << int32_t(31));
}

double FastMath::pow(double a, double b)
{
    auto const x = static_cast< int32_t >((::java::lang::Double::doubleToLongBits(a) >> int32_t(32)));
    auto const y = static_cast< int32_t >((b * (x - int32_t(1072632447)) + int32_t(1072632447)));
    return ::java::lang::Double::longBitsToDouble((static_cast< int64_t >(y)) << int32_t(32));
}

double FastMath::exp(double val)
{
    clinit();
    auto const tmp = static_cast< int64_t >((int32_t(1512775) * val)) + int32_t(1072632447);
    return ::java::lang::Double::longBitsToDouble(tmp << int32_t(32));
}

double FastMath::ln(double val)
{
    clinit();
    double const x = ::java::lang::Double::doubleToLongBits(val) >> int32_t(32);
    return (x - int32_t(1072632447)) / int32_t(1512775);
}
*/

float FastMath::tanh(float x)
{
	if (x < -3.0f)
		return -1.0f;

	if (x > 3.0f)
		return 1.0f;

	auto const x2 = x * x;
	return x * (27.0f + x2) / (27.0f + 9.0f * x2);
}
