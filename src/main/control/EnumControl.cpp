#include <control/EnumControl.hpp>

#include <string>
#include <stdio.h>

using namespace std;
using namespace ctoot::control;

using namespace nonstd;

EnumControl::EnumControl(int id, string name, nonstd::any value) : Control(id, name)
{
	this->value = value;
}

void EnumControl::setValue(nonstd::any value)
{
	if (!isEnabled()) return;

	if (!isValueSupported(value)) {
		MLOG("EnumControl::setValue(), requested value is not supported.");
		return;
	}
	this->value = value;
	notifyParent(this);
	return;
}

nonstd::any EnumControl::getValue()
{
	return value;
}

bool EnumControl::isValueSupported(nonstd::any value)
{
	/*
	try {
		for (int i = 0; i < getValues().size(); i++) {
			if (value.type() == this->value.type()) {
				if (string(value.type().name()).find("int") != string::npos) {
					int i1 = nonstd::any_cast<int>(value);
					int i2 = nonstd::any_cast<int>(this->value);
					if (i1 == i2) {
						return true;
					}
				}
				else {
					string s1 = nonstd::any_cast<string>(value);
					string s2 = nonstd::any_cast<string>(this->value);
					if (s1.compare(s2) == 0) {
						return true;
					}
				}
			}
		}
	}
	catch (const std::exception const &e) {
		string msg = e.what();
		MLOG("EnumControl value not supported, error msg: " + msg);
	}
	*/
	return true;
}

string EnumControl::toString()
{
	string res = getName().append(" with current value: ").append("getValue()");
	return res;
}

string EnumControl::getValueString()
{
	try {
		int i = nonstd::any_cast<int>(getValue());
		return to_string(i);
	}
	catch (std::exception& e1) {
		//printf("Bad anycast, but will try cast to string\n");
		//printf(e1.what());
		try {
			string s = nonstd::any_cast<string>(getValue());
			return s;
		}
		catch (std::exception& e2) {
			//printf(e2.what());
		}
	}
	return nullptr;
}

void EnumControl::setIntValue(int value)
{
	auto values = getValues();
	if (value >= values.size()) return;
	try {
		setValue(getValues()[value]);
	}
	catch (const exception& e) {
        printf("%s", e.what());
	}
}

int EnumControl::getIntValue()
{
	//MLOG("EnumControl getIntValue() is expected to work!");
	int index;
	for (index = 0; index < getValues().size(); index++) {
		auto v = getValues()[index];
		try {
			auto s1 = nonstd::any_cast<string>(v);
			auto s2 = nonstd::any_cast<string>(getValue());
			if (s1.compare(s2) == 0) return index;
		}
		catch (const std::exception& e) {
		}
	}
	return -1;
}

int EnumControl::getWidthLimit()
{
	return 40;
}

bool EnumControl::hasLabel()
{
	return false;
}
