#include <control/LawControl.hpp>
#include <control/ControlLaw.hpp>

using namespace ctoot::control;
using namespace std;

LawControl::LawControl(int id, string name, weak_ptr<ControlLaw> law, float precision, float initialValue) 
	: Control(id, name)
{
	this->law = law;
	this->precision = precision;
	this->value = initialValue;
}

int LawControl::calculateDecimalPlaces()
{
    return law.lock()->getMaximum() - law.lock()->getMinimum() > 100.0f ? 1 : 2;
}

weak_ptr<ControlLaw> LawControl::getLaw()
{
    return law;
}

float LawControl::getValue()
{
    return value;
}

string LawControl::getValueString()
{
	string res1 = law.lock()->getUnits();
	string res2 = to_string(getValue());
	return string(res1 + res2);
}

void LawControl::setValue(float value)
{
	if (!isEnabled()) return;
	this->value = value;
	notifyParent(this);
}

float LawControl::getPrecision()
{
    return precision;
}

void LawControl::setIntValue(int value)
{
    setValue(law.lock()->userValue(value));
}

int LawControl::getIntValue()
{
    return law.lock()->intValue(getValue());
}

vector<string> LawControl::getPresetNames()
{
	return {};
}

void LawControl::applyPreset(string name)
{
}

LawControl::~LawControl() {
}
