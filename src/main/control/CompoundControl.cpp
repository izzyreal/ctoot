#include <control/CompoundControl.hpp>
#include <control/Control.hpp>

using namespace ctoot::control;
using namespace std;

#include <System.hpp>

shared_ptr<CompoundControlPersistence> CompoundControl::persistence;

CompoundControl::CompoundControl(int id, string name) 
	: CompoundControl(id, deriveInstanceIndex(name), name)
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

CompoundControl::CompoundControl(int id, int instanceIndex, string name) : Control(id, name)
{
	this->instanceIndex = instanceIndex;
	providerId = CompoundControl::USE_PARENT_PROVIDER_ID;
	checkInstanceIndex(instanceIndex);
	this->instanceIndex = instanceIndex;
}

int CompoundControl::deriveInstanceIndex(string name)
{
	int result;
	auto hash = name.find('#');
	result = hash != string::npos ? stoi(name.substr(hash + 1)) - 1 : 0;
	return result;
}

const int CompoundControl::USE_PARENT_PROVIDER_ID;

void CompoundControl::checkInstanceIndex(int index)
{
	// toot2 for Java was checking this based on a subclass (AudioControlsChain) call from the constructor. C++ can't do this. For now we don't check.
	if (index < 0) {
		//string desc = getName() + " instance " + to_string(index) + " < 0\n";
		//MLOG(desc);
	}
	if (index > getMaxInstance()) {
		//string desc = getName() + " instance " + to_string(index) + " > " + to_string(getMaxInstance()) + "\n";
		//MLOG(desc);
	}
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

vector<weak_ptr<Control>> CompoundControl::getMemberControls()
{
    return weakControls;
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

bool CompoundControl::isAlwaysVertical()
{
    return false;
}

bool CompoundControl::isAlwaysHorizontal()
{
    return false;
}

bool CompoundControl::isNeverBordered()
{
    return false;
}

float CompoundControl::getAlignmentY()
{
    return -1.0f;
}

string* CompoundControl::getAlternate()
{
    return nullptr;
}

int CompoundControl::getInstanceIndex()
{
    return instanceIndex;
}

weak_ptr<Control> CompoundControl::findByTypeIdName(string typeIdName)
{
	for (int i = 0; i < controls.size(); i++) {
        auto control = controls[i].get();
        auto currentTypeIdName = typeid(*control).name();
		string currentDemangledTypeIdName = moduru::System::demangle(currentTypeIdName);
		
        if (currentDemangledTypeIdName.compare(typeIdName) == 0) {
			return controls[i];
		}
	}
	return {};
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

weak_ptr<CompoundControl> CompoundControl::find(int providerId, int moduleId, int instanceIndex)
{
	for (int i = 0; i < controls.size(); i++) {
		auto currentControl = controls[i];
		auto currentCompoundControl = dynamic_pointer_cast<CompoundControl> (currentControl);
		if (!currentCompoundControl)
			continue;
		if (providerId == currentCompoundControl->getProviderId() 
			&& moduleId == currentCompoundControl->getId() 
			&& instanceIndex == currentCompoundControl->getInstanceIndex()) {
			
			return currentCompoundControl;

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

weak_ptr<CompoundControlPersistence> CompoundControl::getPersistence()
{
    return persistence;
}

void CompoundControl::setPersistence(shared_ptr<CompoundControlPersistence> p)
{
    persistence = p;
}

bool CompoundControl::canBeMoved()
{
    return true;
}

bool CompoundControl::canBeMovedBefore()
{
    return true;
}

bool CompoundControl::canBeInsertedBefore()
{
    return true;
}

bool CompoundControl::canBeDeleted()
{
    return true;
}

bool CompoundControl::canBeMinimized()
{
    return false;
}

bool CompoundControl::hasPresets()
{
    return true;
}

bool CompoundControl::hasCustomUI()
{
    return false;
}

bool CompoundControl::canLearn()
{
    return false;
}

bool CompoundControl::getLearn()
{
    return false;
}

void CompoundControl::setLearn(bool learn)
{
}

string CompoundControl::getPersistenceDomain()
{
	return getParent()->getPersistenceDomain();
}

bool CompoundControl::isPluginParent()
{
    return false;
}

int CompoundControl::getProviderId()
{
	if (providerId == USE_PARENT_PROVIDER_ID) {
		return getParent()->getProviderId();
	}
	return providerId;
}

void CompoundControl::setProviderId(int id)
{
    providerId = id;
}

void CompoundControl::setInstanceIndex(int idx)
{
    instanceIndex = idx;
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
	c.lock()->setInstanceIndex(index - 1);
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

CompoundControl::~CompoundControl() {
}
