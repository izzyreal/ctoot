#include <synth/SynthChannelControls.hpp>
#include <control/BooleanControl.hpp>
#include <control/Control.hpp>
#include <control/ControlLaw.hpp>
#include <control/EnumControl.hpp>
#include <control/FloatControl.hpp>
#include <synth/ControlChange.hpp>

//#include <observer/Observable.hpp>
//#include <concurrentqueue.h>

using namespace ctoot::synth;
using namespace ctoot::control;
using namespace std;

SynthChannelControls::SynthChannelControls(int id, string name)
	: CompoundControl(id, name)
{
}

void SynthChannelControls::close()
{
	if (observable != nullptr) {
		observable->deleteObserver(this);
	}
	/*
	if (changeThread != nullptr) {
		changeThread = nullptr;
		{
			//synchronized synchronized_0(this);
			//notify();
		}
	}
	*/
}

void SynthChannelControls::notifyParent(Control* obj)
{
    if(learn) {
        learnControl = obj;
    }
    CompoundControl::notifyParent(obj);
}

void SynthChannelControls::ensureMapExists()
{
	if (map.size() != 128) map = vector<Control*>(128);
}

void SynthChannelControls::update(moduru::observer::Observable* o, nonstd::any a)
{

	if (dynamic_cast<ControlChange*>(o) == nullptr) return;
	if (observable == nullptr) observable = o;
	auto change = dynamic_cast<ControlChange*>(o);
	auto controller = change->getController();
	if (controller >= 32 && controller < 64) return;

	if (learn && learnControl != nullptr) {
		ensureMapExists();
		map.insert(map.begin() + controller, learnControl);
		learn = false;
		learnControl = nullptr;
	}
	if (map.size() == 128 && map[controller] != nullptr) {
		//if (changeQueue == nullptr) {
			//changeQueue = new concurrent_queue<ControlChange*>;
			//changeThread = new std::thread(run(), getName() + " CC");
			//changeThread->start();
		//}
		changeQueue.try_enqueue(change);
		//            synchronized synchronized_1(this);
			//notify();
	}
}

SynthChannelControls::~SynthChannelControls() {
	for (auto& c : map) {
		if (c != nullptr) {
			delete c;
		}
	}
}
