#include "Control.hpp"

#include "CompoundControl.hpp"

using namespace ctoot::control;
using namespace std;

Control::Control(int id, string name)
{
	this->name = name;
	this->id = id;
	annotation = name;
}

void Control::setHidden(bool h)
{
    hidden = h;
}

int Control::getId()
{
    return id;
}


CompoundControl* Control::getParent()
{
    return parent;
}

void Control::setParent(CompoundControl* c)
{
	parent = c;
}

void Control::notifyParent(Control* c)
{

	derive(c);
	
	if (c->isIndicator()) return;

	if (parent != nullptr) {
		parent->notifyParent(c);
	}
}

void Control::derive(Control* obj)
{
}

string Control::getName()
{
    return name;
}

void Control::setName(string s)
{
    name = s;
    annotation = s;
}

void Control::setAnnotation(string a)
{
    annotation = a;
}

int Control::getIntValue()
{
    return -1;
}

string Control::getValueString()
{
	return string("");
}

bool Control::isHidden()
{
    return hidden;
}

bool Control::isIndicator()
{
    return indicator;
}

void Control::setEnabled(bool enable)
{
    enabled = enable;
}

bool Control::isEnabled()
{
    return enabled;
}

string Control::getControlPath(Control* from, string sep)
{
	if (parent != from) {
		if (getName().length() > 0) {
			string result = parent->getControlPath(from, sep) + sep + getName();
			return result;
		}
		else {
			return parent->getControlPath(from, sep);
		}
	}
	return getName();

}
