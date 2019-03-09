#include <control/IntegerControl.hpp>

#include <control/IntegerLaw.hpp>

#include <cmath>

using namespace ctoot::control;
using namespace std;

IntegerControl::IntegerControl(int32_t id, string name, weak_ptr<IntegerLaw> law, float precision, int32_t initialValue)
	: FloatControl(id, name, dynamic_pointer_cast<ControlLaw>(law.lock()), precision, initialValue)
{
}

int32_t IntegerControl::getUserValue()
{
    return round(getValue());
}

string IntegerControl::getValueString()
{
    return to_string(getUserValue());
}
