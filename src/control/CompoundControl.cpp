#include <control/CompoundControl.hpp>
//#include <control/CompoundControlPersistence.hpp>
#include <control/Control.hpp>

using namespace ctoot::control;
using namespace std;

CompoundControl::CompoundControl(int id, string name) 
	: CompoundControl(id, deriveInstanceIndex(name), name) {

}

std::vector<std::string> CompoundControl::getControlNamesRecursive(int generation) {
	std::vector<std::string> res;
	std::string indent;
	for (int i = 0; i < generation; i++) {
		indent += "     ";
	}
	res.push_back("\n" + indent + getName() + " has these controls:");
	for (auto& c : controls) {
		res.push_back(indent + c->getName());
	}
	for (auto& c : controls) {
		auto cc = dynamic_pointer_cast<CompoundControl>(c);
		if (cc) {
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

int CompoundControl::deriveInstanceIndex(string name) {
	int result;
	int hash = (int)(name.find('#'));
	result = hash > 0 ? stoi(name.substr(hash + 1)) - 1 : 0;
	return result;
}

const int CompoundControl::USE_PARENT_PROVIDER_ID;

/*
CompoundControlPersistence*& CompoundControl::persistence()
{
    return persistence_;
}
CompoundControlPersistence* CompoundControl::persistence_;
*/

void CompoundControl::checkInstanceIndex(int index)
{
	if (index < 0) {
		string desc = getName() + " instance " + to_string(index) + " < 0\n";
		//printf("%s", desc.c_str());
	}
	if (index > getMaxInstance()) {
		string desc = getName() + " instance " + to_string(index) + " > " + to_string(getMaxInstance()) + "\n";
		//printf("%s", desc.c_str());
	}
}

int CompoundControl::getMaxInstance()
{
    return 8 - 1;
}

void CompoundControl::add(shared_ptr<Control> control)
{
	if (control == nullptr) return;
	control->setParent(this);
	string name = control->getName();
	controls.push_back(std::move(control));
}

void CompoundControl::remove(weak_ptr<Control> c)
{
	auto control = c.lock();
	if (!control) return;
	for (int i = 0; i < controls.size(); i++) {
		auto currentControl = controls[i];
		if (currentControl == control) {
			controls.erase(controls.begin() + i);
			control->setParent(nullptr);
			control.reset();
			break;
		}
	}
}

vector<weak_ptr<Control>> CompoundControl::getMemberControls()
{
	vector<weak_ptr<Control>> res;
	for (auto& c : controls)
		res.push_back(c);
	return res;
}

vector<weak_ptr<Control>> CompoundControl::getControls()
{
	vector<weak_ptr<Control>> res;
	for (auto& c : controls)
		res.push_back(c);
	return res;
}

string CompoundControl::toString()
{
	vector<string>* builder;
	for (auto i = 0; i < controls.size(); i++) {
		if (i != 0) {
			builder->push_back(", ");
			if ((i + 1) == controls.size()) {
				builder->push_back("and ");
			}
		}
		builder->push_back(controls[i]->getName());
	}

	string result;
	for (int i = 0; i < builder->size(); i++)
		result += (*builder)[i];

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
		string currentTypeIdName = typeid(*controls[i].get()).name();
		if (currentTypeIdName.compare(typeIdName) == 0) {
			return controls[i];
		}
	}
	return {};
}

weak_ptr<Control> CompoundControl::find(string name)
{
	//MLOG("Attempting to find compound control by string, arg == " + name);
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
	for (int i = 0; i < controls.size(); i++) {
		auto currentControl = controls[i];
		auto currentCompoundControl = dynamic_pointer_cast<CompoundControl>(currentControl);
		if (!currentCompoundControl)
			continue;
		auto deepFoundControl = currentCompoundControl->deepFind(controlId).lock();
		if (deepFoundControl) {
			return deepFoundControl;
		}
		else if (controlId == currentControl->getId()) {
			return controls[i];
		}
	}
	return {};
}

/*
CompoundControlPersistence* CompoundControl::getPersistence()
{
    return persistence_;
}

void CompoundControl::setPersistence(CompoundControlPersistence* p)
{
    persistence_ = p;
}
*/

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
