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

float FastMath::tanh(float x)
{
	if (x < -3.0f)
		return -1.0f;

	if (x > 3.0f)
		return 1.0f;

	auto const x2 = x * x;
	return x * (27.0f + x2) / (27.0f + 9.0f * x2);
}
