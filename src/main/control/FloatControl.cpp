#include <control/FloatControl.hpp>
#include <control/ControlLaw.hpp>

using namespace ctoot::control;
using namespace std;

FloatControl::FloatControl(int id, string name, weak_ptr<ControlLaw> law, float precision, float initialValue, string minLabel, string midLabel, string maxLabel) 
	: LawControl(id, name, law, precision, initialValue)
{
	this->minLabel = minLabel;
	this->midLabel = midLabel;
	this->maxLabel = maxLabel;
}

bool FloatControl::isRotary()
{
    return true;
}

float FloatControl::getMaximum()
{
    return getLaw().lock()->getMaximum();
}

float FloatControl::getMinimum()
{
    return getLaw().lock()->getMinimum();
}

string FloatControl::getMinLabel()
{
    return minLabel;
}

string FloatControl::getMidLabel()
{
    return midLabel;
}

string FloatControl::getMaxLabel()
{
    return maxLabel;
}

string FloatControl::toString()
{
//    return stringBuilder().append(getName())->append(" with current value: "
//        ->append(getValue())
//        ->append(" "
//        ->append(getLaw()->getUnits())
//        ->append(" (range: "
//        ->append(getMinimum())
//        ->append(" - "
//        ->append(getMaximum())
//        ->append(")"->toString();
	return "fix the method izzy!";
}

FloatControl::~FloatControl() {
}
