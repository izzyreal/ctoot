#include "Control.hpp"

#include "CompoundControl.hpp"
#include "ChainMutation.hpp"

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
//    printf("registerType %s\n", name.c_str());
	(*getRegistry())[name] = factory;
//    printf("registrySize %i\n", (int)(*getRegistry()).size());
}

shared_ptr<Control> Control::create(const std::string &name)
{
    //MLOG("Registry size: " + to_string(getRegistry()->size()));
    //MLOG("Registry contains: ");
	for (auto& s : *getRegistry()) {
        //MLOG(s.first);
		if (s.second == nullptr) {
            //MLOG(s.first + " factory is nullptr!");
		}
	}
    //MLOG("Trying to create " + name);
	auto res = (*getRegistry())[name]->create();
	auto namestr = res->getName();
    //MLOG("Created control name: " + namestr);
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

string Control::getAnnotation()
{
    return annotation;
}

void Control::setAnnotation(string a)
{
    annotation = a;
}

void Control::setIntValue(int value)
{
	string description = "ERROR: Unexpected setIntValue(" + to_string(value) + ") called on " + getControlPath();
	MLOG(description);
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

bool Control::isAdjusting()
{
    return adjusting;
}

void Control::setAdjusting(bool state)
{
    adjusting = state;
    notifyParent(this);
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

string Control::getControlPath()
{
	return getControlPath(nullptr, "/");
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
