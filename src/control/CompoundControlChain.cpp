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

void CompoundControlChain::add(shared_ptr<CompoundControl> control)
{
	if (find(control->getName()).lock()) {
		disambiguate(control);
	}
	CompoundControl::add(control);
}

void CompoundControlChain::add(int index, shared_ptr<CompoundControl> control)
{
	controls.insert(controls.begin() + index, control);
	control->setParent(this);
}

void CompoundControlChain::insert(string insertName, string insertBeforeName)
{
	auto controlToInsert = createControl(insertName);
	if (!controlToInsert) {
		string error = getName() + ": insert failed to create " + insertName;
		MLOG("CompoundControlChain::insert error: " + error);
		return;
	}
	if (find(insertName).lock()) {
		disambiguate(controlToInsert);
	}
	insert(shared_ptr<Control>(controlToInsert), insertBeforeName);
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
		if (controls[i] == controlToInsertBefore) insertionIndex = i;
	}
	controls.insert(controls.begin() + insertionIndex, shared_ptr<Control>(controlToInsert));
	controlToInsert->setParent(this);
	ChainMutation* newccccm = new ChainMutation(ChainMutation::INSERT, (int)(insertionIndex));
	setChanged();
	notifyObservers(newccccm);
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
	setChanged();
	notifyObservers(new ChainMutation(ChainMutation::DELETE, index));
}

void CompoundControlChain::delete_(int indexToDelete)
{
	remove(controls[indexToDelete]);
	setChanged();
	notifyObservers(new ChainMutation(ChainMutation::DELETE, indexToDelete));
}

void CompoundControlChain::move(string moveName, string moveBeforeName)
{
	auto controlToMove = find(moveName).lock();
	auto controlToMoveBefore = find(moveBeforeName).lock();
	if (!controlToMove || !controlToMoveBefore ) return;
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
	setChanged();
	notifyObservers(new ChainMutation(ChainMutation::MOVE, indexToMove, insertionIndex));
}

void CompoundControlChain::setMutating(bool mutating)
{
	setChanged();
	notifyObservers(mutating ? ChainMutation::COMMENCE_INSTANCE() : ChainMutation::COMPLETE_INSTANCE());
}


bool CompoundControlChain::isPluginParent()
{
    return true;
}

CompoundControlChain::~CompoundControlChain() {
}
