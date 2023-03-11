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

