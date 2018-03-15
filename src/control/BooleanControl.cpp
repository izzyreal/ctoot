#include <control/BooleanControl.hpp>

using namespace ctoot::control;
using namespace std;

BooleanControl::BooleanControl(int id, string name, bool initialValue) 
	: BooleanControl(id, name, initialValue, "On", "Off")
{
	momentary = false;
}


BooleanControl::BooleanControl(int id, string name, bool initialValue, bool momentary) 
	: BooleanControl(id, name, initialValue)
{
	this->momentary = momentary;
}

BooleanControl::BooleanControl(int id, string name, bool initialValue, string trueStateLabel, string falseStateLabel) 
	: Control(id, name)
{
	momentary = false;
	this->value = initialValue;
	this->trueStateLabel = trueStateLabel;
	this->falseStateLabel = falseStateLabel;
}

bool BooleanControl::isMomentary()
{
    return momentary;
}

void BooleanControl::setValue(bool value)
{
	if (!isEnabled())
		return;

	if (value != this->value) {
		this->value = value;
		notifyParent(this);
	}
}

void BooleanControl::momentaryAction()
{
}

bool BooleanControl::getValue()
{
    return value;
}

string BooleanControl::getStateLabel(bool state)
{
    return state ? trueStateLabel : falseStateLabel;
}

string BooleanControl::toString()
{
	return Control::toString() + " with current value: " + getStateLabel(getValue());
}

string BooleanControl::getValueString()
{
    return isMomentary() ? "" : getStateLabel(getValue());
}

void BooleanControl::setIntValue(int value)
{
    setValue(value == 0 ? false : true);
}

int BooleanControl::getIntValue()
{
	return getValue() ? 1 : 0;
}

int BooleanControl::getWidthLimit()
{
    return 42;
}
