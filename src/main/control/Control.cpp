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

void Control::registerType(const std::string& name, ControlFactory *factory)
{
	(*getRegistry())[name] = factory;
}

shared_ptr<Control> Control::create(const std::string &name)
{
	auto res = (*getRegistry())[name]->create();
	auto namestr = res->getName();
	return res;
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
	if (parent == nullptr) {
		MLOG("Parent for " + getName() + " is nullptr!");
	}
}

void Control::notifyParent(Control* c)
{

	derive(c);
	
	notifyObservers(c);
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

string Control::toString()
{
	string result = getName() + " Control";
	return result;
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

Control::~Control() {
}
