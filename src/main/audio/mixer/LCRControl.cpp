#include "LCRControl.hpp"

#include <audio/mixer/MixControlIds.hpp>

using namespace ctoot::audio::mixer;
using namespace std;

LCRControl::LCRControl(string name, weak_ptr<ctoot::control::ControlLaw> law, float precision, float initialValue)
	: FloatControl(MixControlIds::LCR, name, law, precision, initialValue)
{
}

vector<string> LCRControl::getPresetNames()
{
	static vector<string> res{ "Center","Left", "Right" };
    return res;
}

void LCRControl::applyPreset(string presetName)
{
//    if(npc(presetName)->equals(static_cast< ::java::lang::Object* >("Center"))) {
//        setValue(0.5f);
//    } else if(npc(presetName)->equals(static_cast< ::java::lang::Object* >("Left"))) {
//        setValue(0.0f);
//    } else if(npc(presetName)->equals(static_cast< ::java::lang::Object* >("Right"))) {
//        setValue(1.0f);
//    }
}

LCRControl::~LCRControl() {
}
