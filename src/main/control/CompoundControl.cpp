#include <control/CompoundControl.hpp>
#include <control/Control.hpp>

using namespace ctoot::control;
using namespace std;

#include <System.hpp>

CompoundControl::CompoundControl(int id, string name) : Control(id, name)
{
}

vector<string> CompoundControl::getControlNamesRecursive(int generation)
{
	vector<string> res;
	string indent;

    for (int i = 0; i < generation; i++)
		indent += "     ";

    res.push_back("\n" + indent + getName() + " has these controls:");
	
    for (auto& c : controls)
		res.push_back(indent + c->getName());

    for (auto& c : controls)
    {
		auto cc = dynamic_pointer_cast<CompoundControl>(c);
	
        if (cc)
        {
			auto strings = cc->getControlNamesRecursive(generation + 1);
		
            for (auto& s : strings)
				res.push_back(s);
		}
	}
    
	return res;
}

int CompoundControl::getMaxInstance()
{
    return 8 - 1;
}

void CompoundControl::add(shared_ptr<Control> control)
{
	if (!control) return;
	string name = control->getName();
	control->setParent(this);
	controls.push_back(move(control));
    weakControls.push_back(controls.back());
}

void CompoundControl::remove(weak_ptr<Control> c)
{
	auto control = c.lock();
	
    if (!control)
        return;
	
    for (int i = 0; i < controls.size(); i++)
    {
		auto currentControl = controls[i];
		
        if (currentControl == control)
        {
			controls.erase(begin(controls) + i);
            weakControls.erase(begin(weakControls) + i);
			break;
		}
	}
}

vector<weak_ptr<Control>> CompoundControl::getControls()
{
    return weakControls;
}

string CompoundControl::toString()
{
	vector<string> builder;
	
    for (auto i = 0; i < controls.size(); i++)
    {
		if (i != 0)
        {
			builder.push_back(", ");
		
            if (controls.size() == i + 1)
				builder.push_back("and ");
		}
        
		builder.push_back(controls[i]->getName());
	}

	string result;
    
	for (int i = 0; i < builder.size(); i++)
		result += builder[i];

	result = " Control containing " + result + " Controls.";
	return result;
}

weak_ptr<Control> CompoundControl::find(string name)
{
	for (int i = 0; i < controls.size(); i++) {
		if (controls[i]->getName().compare(name) == 0) {
			return controls[i];
		}
	}
	return {};
}

weak_ptr<Control> CompoundControl::deepFind(int controlId)
{
	for (auto& c : controls) {

		auto cc = dynamic_pointer_cast<CompoundControl>(c);

		if (cc) {
			auto c2 = cc->deepFind(controlId).lock();
			if (c2) return c2;

		}
		else if (controlId == c->getId()) {
			return c;
		}
	
	}
	return {};
}

void CompoundControl::disambiguate(weak_ptr<CompoundControl> c)
{
	auto original = c.lock()->getName();
	if (!find(original).lock()) {
		return;
	}
	int index = 1;
	string str;
	do {
		index++;
		str = original + " #" + (to_string(index));
	} while (find(str).lock());
	c.lock()->setName(str);
}

void CompoundControl::close()
{
}

void CompoundControl::setEnabled(bool enable)
{
	Control::setEnabled(enable);
	for (int i = 0; i < controls.size(); i++) {
		Control* currentControl = controls[i].get();
		currentControl->setEnabled(enable);
	}
}
