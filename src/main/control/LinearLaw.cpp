#include <control/LinearLaw.hpp>

using namespace ctoot::control;
using namespace std;

LinearLaw::LinearLaw(float min, float max, string units)
	: AbstractLaw(min, max, units)
{
}

weak_ptr<LinearLaw> LinearLaw::UNITY()
{
	static shared_ptr<LinearLaw> res = make_shared<LinearLaw>(0, 1, "");
	return res;
}

int LinearLaw::intValue(float v)
{
    return static_cast< int >((resolution - 1) * (v - min) / (max - min));
}

float LinearLaw::userValue(int v)
{
    return min + (max - min) * (static_cast< float >(v) / (resolution - 1));
}
