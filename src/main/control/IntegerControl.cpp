#include <control/IntegerControl.hpp>

#include <control/IntegerLaw.hpp>

#include <cmath>

using namespace ctoot::control;
using namespace std;

int32_t IntegerControl::getUserValue()
{
    return round(getValue());
}

string IntegerControl::getValueString()
{
    return to_string(getUserValue());
}
