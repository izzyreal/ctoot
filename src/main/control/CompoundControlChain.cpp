#include <control/CompoundControlChain.hpp>
#include <control/CompoundControl.hpp>
#include <control/ChainMutation.hpp>
#include <control/Control.hpp>
#include <algorithm>

using namespace ctoot::control;
using namespace std;

CompoundControlChain::CompoundControlChain(int id, string name)
	: CompoundControl(id, name)
{
}

CompoundControlChain::CompoundControlChain(int id, int index, string name)
	: CompoundControl(id, index, name)
{
}

void CompoundControlChain::add(shared_ptr<Control> control)
{
	if (find(control->getName()).lock()) {
		disambiguate(dynamic_pointer_cast<CompoundControl>(control));
	}
	CompoundControl::add(control);
}

void CompoundControlChain::add(int index, shared_ptr<Control> control)
{
	control->setParent(this);
	controls.insert(controls.begin() + index, std::move(control));
}

void CompoundControlChain::insert(string insertName, string insertBeforeName)
{
	auto controlToInsert = createControl(insertName);
	if (!controlToInsert) {
		string error = getName() + ": insert failed to create " + insertName;
		MLOG("CompoundControlChain::insert error: " + error);
		return;
	}
	if (find(insertName).lock() || find(controlToInsert->getName()).lock()) {
		disambiguate(controlToInsert);
	}
	insert(controlToInsert, insertBeforeName);
}

void CompoundControlChain::insert(shared_ptr<Control> controlToInsert, string insertBeforeName)
{
	auto insertionIndex = controls.size();
	auto controlToInsertBefore = find(insertBeforeName).lock();
	if (!controlToInsertBefore) {
		string error = getName() + ": insert " + controlToInsert->getName() + ", " + insertBeforeName + " not found to insert before";
		MLOG(error);
		return;
	}
	if (!dynamic_pointer_cast<CompoundControl>(controlToInsertBefore)->canBeInsertedBefore()) {
		string error = getName() + ": insert " + controlToInsert->getName() + " before " + insertBeforeName + " not allowed";
		MLOG(error);
		return;
	}
	for (int i = 0; i < controls.size(); i++) {
		if (controls[i] == controlToInsertBefore) {
			insertionIndex = i;
			break;
		}
	}
	controlToInsert->setParent(this);
	ChainMutation* insertMutation = new InsertMutation((int)(insertionIndex), controlToInsert);
	controls.insert(controls.begin() + insertionIndex, std::move(controlToInsert));
	
	notifyObservers(insertMutation);
}

shared_ptr<CompoundControl> CompoundControlChain::createControl(string name)
{
	MLOG("CompoundControlChain::createControl empty function called!");
	return {};
}


void CompoundControlChain::delete_(string deleteName)
{
	auto controlToDelete = find(deleteName).lock();
	int index;
	for (index = 0; index < controls.size(); index++) {
		if (controls[index] == controlToDelete) {
			break;
		}
	}
	remove(controlToDelete);
	ChainMutation* m = new DeleteMutation(index);
	
	notifyObservers(m);
}

void CompoundControlChain::delete_(int indexToDelete)
{
	remove(controls[indexToDelete]);
	ChainMutation* m = new DeleteMutation(indexToDelete);
	
	notifyObservers(m);
}

void CompoundControlChain::move(string moveName, string moveBeforeName)
{
	auto controlToMove = find(moveName).lock();
	auto controlToMoveBefore = find(moveBeforeName).lock();
	if (!controlToMove || !controlToMoveBefore) return;
	int indexToMove = 0;
	for (indexToMove = 0; indexToMove < controls.size(); indexToMove++) {
		if (controls[indexToMove] == controlToMove) {
			break;
		}
	}
	remove(controlToMove);
	int insertionIndex = 0;
	for (insertionIndex = 0; insertionIndex < controls.size(); insertionIndex++) {
		if (controls[insertionIndex] == controlToMoveBefore) {
			break;
		}
	}
	controls.insert(controls.begin() + insertionIndex, controlToMove);
	ChainMutation* m = new MoveMutation(indexToMove, insertionIndex);
	
	notifyObservers(m);
}

void CompoundControlChain::setMutating(bool mutating)
{
	
	notifyObservers(mutating ? ChainMutation::COMMENCE_INSTANCE() : ChainMutation::COMPLETE_INSTANCE());
}


bool CompoundControlChain::isPluginParent()
{
	return true;
}

CompoundControlChain::~CompoundControlChain() {
}
