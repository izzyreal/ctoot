#include "LinkControl.hpp"

#include <audio/dynamics/izcompressor/IzBandCompressorControls.hpp>

#include <audio/dynamics/DynamicsControlIds.hpp>
#include <control/LogLaw.hpp>

using namespace ctoot::audio::dynamics::izcompressor;
using namespace std;

LinkControl::LinkControl(int idOffset, string name, weak_ptr<ctoot::control::IntegerLaw> law, vector<weak_ptr<IzBandCompressorControls>> controls)
	: ctoot::control::IntegerControl(DynamicsControlIds::CROSSOVER_FREQUENCY + idOffset, name, law, 1.0f, 0)
{
	this->controls = controls;
}

void LinkControl::setValue(float value) {
	IntegerControl::setValue(value);
	int linkIndex = value - 1;
	if (linkIndex == -1) {
		for (auto& c : controls)
			c.lock()->setLink({});
	}
	else {
		for (int i = 0; i < controls.size(); i++) {
			auto cl = controls[i].lock();
			if (i == linkIndex) {
				cl->setLink({});
			}
			else {
				cl->setLink(controls[linkIndex]);
			}
			cl->deriveIndependentVariables();
			cl->deriveDependentVariables();
		}
	}

}

