#include "TrimControl.hpp"

#include <dsp/VolumeUtils.hpp>

using namespace ctoot::audio::basic::trim;
using namespace ctoot::dsp;

using namespace std;

TrimControl::TrimControl(int id, string name, weak_ptr<ControlLaw> law, float precision, float initialValue, float* trimToSet)
	: FloatControl(id, name, law, precision, initialValue)
{
	this->trimToSet = trimToSet;
}

void TrimControl::derive(Control* control)
{
	*trimToSet = (float) VolumeUtils::log2lin(getValue());
}

TrimControl::~TrimControl()
{

}
