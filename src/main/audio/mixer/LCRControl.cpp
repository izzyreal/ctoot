#include "LCRControl.hpp"

#include <audio/mixer/MixControlIds.hpp>

using namespace ctoot::audio::mixer;
using namespace std;

LCRControl::LCRControl(string name, weak_ptr<ctoot::control::ControlLaw> law, float precision, float initialValue)
	: FloatControl(MixControlIds::LCR, name, law, precision, initialValue)
{
}

LCRControl::~LCRControl() {
}
