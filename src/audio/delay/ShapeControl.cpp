#include <audio/delay/ShapeControl.hpp>

using namespace ctoot::audio::delay;
using namespace std;

vector<string> ShapeControl::values{ "Sin", "Tri" };

ShapeControl::ShapeControl(int id)
	: EnumControl(id, "Shape", values[0])
{
}

vector<boost::any> ShapeControl::getValues()
{
	vector<boost::any> res;
	for (auto& s : values)
		res.push_back(s);
    return res;
}

bool ShapeControl::hasLabel()
{
    return true;
}
