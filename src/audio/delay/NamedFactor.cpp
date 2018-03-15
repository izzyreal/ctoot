#include "NamedFactor.hpp"

using namespace ctoot::audio::delay;

NamedFactor::NamedFactor(float factor, std::string name)
{
    this->factor = factor;
    this->name = name;
}

float NamedFactor::getFactor()
{
    return factor;
}

std::string NamedFactor::toString()
{
    return name;
}
