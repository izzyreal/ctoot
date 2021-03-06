#include <control/ChainMutation.hpp>

#include <Logger.hpp>

using namespace ctoot::control;
using namespace std;

ChainMutation::ChainMutation(int type)
{
	if (type != COMMENCE && type != COMPLETE) {
		MLOG("ChainMutation:illegal no indices constructor for this type");
		return;
	}
	this->type = type;
}

ChainMutation::ChainMutation(int type, int index) 
{
	this->type = type;
	index0 = index;
}

ChainMutation::ChainMutation(int type, int index0, int index1) : ChainMutation(type, index0)
{
	this->index1 = index1;
}

const int ChainMutation::DELETE;
const int ChainMutation::INSERT;
const int ChainMutation::MOVE;
const int ChainMutation::COMMENCE;
const int ChainMutation::COMPLETE;

ChainMutation*& ChainMutation::COMMENCE_INSTANCE()
{
    return COMMENCE_INSTANCE_;
}
ChainMutation* ChainMutation::COMMENCE_INSTANCE_ = new ChainMutation(COMMENCE);

ChainMutation*& ChainMutation::COMPLETE_INSTANCE()
{
    return COMPLETE_INSTANCE_;
}
ChainMutation* ChainMutation::COMPLETE_INSTANCE_ = new ChainMutation(COMPLETE);

int ChainMutation::getType()
{
    return type;
}

int ChainMutation::getIndex0()
{
    return index0;
}

int ChainMutation::getIndex1()
{
    return index1;
}

string ChainMutation::toString()
{
//    return stringBuilder().append(typeName())->append(&string("("
//        ->append(index0)
//        ->append(&string(", "
//        ->append(index1)
//        ->append(&string(")"->toString();
	return typeName();
}

string ChainMutation::typeName()
{
    switch (type) {
    case DELETE:
        return string("Delete");
    case INSERT:
        return string("Insert");
    case MOVE:
        return string("Move");
    case COMMENCE:
        return string("Commence");
    case COMPLETE:
        return string("Complete");
    }

    return string("unknown mutation");
}

DeleteMutation::DeleteMutation(int index) : ChainMutation(ChainMutation::DELETE, index) {}

InsertMutation::InsertMutation(int index, weak_ptr<Control> c) : ChainMutation(ChainMutation::INSERT, index) {
	this->control = c;
}

weak_ptr<Control> InsertMutation::getControl() {
	return control;
}

MoveMutation::MoveMutation(int index0, int index1) : ChainMutation(ChainMutation::MOVE, index0) {
	this->index1 = index1;
}
