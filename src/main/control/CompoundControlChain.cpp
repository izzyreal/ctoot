#include <control/CompoundControlChain.hpp>
#include <control/CompoundControl.hpp>
#include <control/Control.hpp>
#include <algorithm>

using namespace ctoot::control;
using namespace std;

CompoundControlChain::CompoundControlChain(int id, string name)
	: CompoundControl(id, name)
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
