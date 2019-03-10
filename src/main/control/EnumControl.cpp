#include <control/EnumControl.hpp>

#include <string>
#include <stdio.h>

using namespace std;
using namespace ctoot::control;

EnumControl::EnumControl(int id, string name, std::any value) : Control(id, name)
{
	this->value = value;
}

void EnumControl::setValue(std::any value)
{
	if (!isEnabled()) return;

	if (!isValueSupported(value)) {
		MLOG("EnumControl::setValue(), requested value is not supported.");
		return;
	}
	this->value = value;
	notifyParent(this);
	return;
	/*
	// Verify that this comparison does what it should do.
	if (value.type() == this->value.type()) {
		if (string(value.type().name()).find("int") != string::npos) {
			int i1 = std::any_cast<int>(value);
			int i2 = std::any_cast<int>(this->value);
			if (i1 != i2) {
				this->value = value;
				notifyParent(this);
			}
		}
		else {
			try {
				string s1 = std::any_cast<string>(value);
				string s2 = std::any_cast<string>(this->value);
				if (s1.compare(s2) != 0) {
					this->value = value;
					notifyParent(this);
				}
			}
			catch (const std::bad_any_cast const &e) {
				string msg = e.what();
				MLOG("EnumControl setValue error, msg: " + msg);
			}
		}
	}
	*/
}

std::any EnumControl::getValue()
{
	return value;
}

bool EnumControl::isValueSupported(std::any value)
{
	/*
	try {
		for (int i = 0; i < getValues().size(); i++) {
			if (value.type() == this->value.type()) {
				if (string(value.type().name()).find("int") != string::npos) {
					int i1 = std::any_cast<int>(value);
					int i2 = std::any_cast<int>(this->value);
					if (i1 == i2) {
						return true;
					}
				}
				else {
					string s1 = std::any_cast<string>(value);
					string s2 = std::any_cast<string>(this->value);
					if (s1.compare(s2) == 0) {
						return true;
					}
				}
			}
		}
	}
	catch (const std::bad_any_cast const &e) {
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
		int i = std::any_cast<int>(getValue());
		return to_string(i);
	}
	catch (std::bad_any_cast& e1) {
		//printf("Bad anycast, but will try cast to string\n");
		//printf(e1.what());
		try {
			string s = std::any_cast<string>(getValue());
			return s;
		}
		catch (std::bad_any_cast& e2) {
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
		printf(e.what());
	}
}

int EnumControl::getIntValue()
{
	//MLOG("EnumControl getIntValue() is expected to work!");
	int index;
	for (index = 0; index < getValues().size(); index++) {
		auto v = getValues()[index];
		try {
			auto s1 = std::any_cast<string>(v);
			auto s2 = std::any_cast<string>(getValue());
			if (s1.compare(s2) == 0) return index;
		}
		catch (const std::bad_any_cast& e) {
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
