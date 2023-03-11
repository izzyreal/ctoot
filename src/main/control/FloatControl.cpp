#include <control/FloatControl.hpp>
#include <control/ControlLaw.hpp>

using namespace ctoot::control;
using namespace std;

FloatControl::FloatControl(int id, string name, weak_ptr<ControlLaw> law, float precision, float initialValue)
	: LawControl(id, name, law, precision, initialValue)
{
}

float FloatControl::getMaximum()
{
    return getLaw().lock()->getMaximum();
}

float FloatControl::getMinimum()
{
    return getLaw().lock()->getMinimum();
}
