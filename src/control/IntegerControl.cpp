#include <control/IntegerControl.hpp>

using namespace ctoot::control;
using namespace std;

IntegerControl::IntegerControl(int32_t id, string name, weak_ptr<IntegerLaw> law, float precision, int32_t initialValue)
	: FloatControl(id, name, law, precision, initialValue)
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
