#include "BarrControls.hpp"

#include <control/ControlColumn.hpp>

#include <cmath>

using namespace std;
using namespace ctoot::audio::reverb;
using namespace ctoot::control;

BarrControls::BarrControls()
	: AudioControls(0x50 + 1, "Barr.Reverb")
{
	createControls();
	deriveControls();
}

int MAX_PRE_DELAY_MS = 200;

weak_ptr<ControlLaw> BarrControls::PRE_DELAY_LAW() {
	static shared_ptr<ControlLaw> res = make_shared<LinearLaw>(0, MAX_PRE_DELAY_MS, "ms");
	return res;
}

weak_ptr<ControlLaw> BarrControls::DIFFUSION_LAW() {
	static shared_ptr<ControlLaw> res = make_shared<LinearLaw>(0, 0.99f, "");
	return res;
}
weak_ptr<ControlLaw> BarrControls::SIZE_LAW() {
	static shared_ptr<LogLaw> res = make_shared<LogLaw>(0.2f, 1.f, "");
	return res;
}

void BarrControls::derive(ctoot::control::Control* c) {
	switch (c->getId()) {
	case PRE_DELAY: preDelaySamples = derivePreDelaySamples(); break;
	case BANDWIDTH: bandwidth = deriveBandwidth(); break;
	case INPUT_DIFFUSION: inputDiffusion = deriveInputDiffusion(); break;
	case DAMPING: damping = deriveDamping(); break;
	case DECAY: decay = deriveDecay(); break;
	case DECAY_DIFFUSION: decayDiffusion = deriveDecayDiffusion(); break;
	case SIZE: size = deriveSize(); break;
	}
}

void BarrControls::createControls() {

	auto preDelayControlShared = createPreDelayControl();
	preDelayControl = preDelayControlShared;
	auto bandwidthControlShared = createBandwidthControl();
	bandwidthControl = bandwidthControlShared;
	auto inputDiffusionControlShared = createInputDiffusionControl();
	inputDiffusionControl = inputDiffusionControlShared;
	auto sizeControlShared = createSizeControl();
	sizeControl = sizeControlShared;
	auto dampingControlShared = createDampingControl();
	dampingControl = dampingControlShared;
	auto decayControlShared = createDecayControl();
	decayControl = decayControlShared;

	auto col1 = std::make_shared<ctoot::control::ControlColumn>();
	col1->add(preDelayControlShared);
	col1->add(bandwidthControlShared);
	add(col1);
	auto col2 = std::make_shared<ctoot::control::ControlColumn>();
	col2->add(inputDiffusionControlShared);
	col2->add(sizeControlShared);
	add(col2);
	auto col3 = std::make_shared<ctoot::control::ControlColumn>();
	col3->add(dampingControlShared);
	col3->add(decayControlShared);
	add(col3);
	//		ControlColumn col4 = new ControlColumn();
	/*		col4.add(decayDiffusionControl = createDecayDiffusionControl()); */
	//		add(col4);
}

std::shared_ptr<ctoot::control::FloatControl> BarrControls::createPreDelayControl() {
	auto control = std::make_shared<ctoot::control::FloatControl>(PRE_DELAY, "Pre", PRE_DELAY_LAW(), 0.1f, 20.f);
	return control;
}

std::shared_ptr<ctoot::control::FloatControl> BarrControls::createBandwidthControl() {
	auto control = std::make_shared<ctoot::control::FloatControl>(BANDWIDTH, "B/W", LinearLaw::UNITY(), 0.01f, 0.95f);
	return control;
}

std::shared_ptr<ctoot::control::FloatControl> BarrControls::createInputDiffusionControl() {
	auto control = std::make_shared<ctoot::control::FloatControl>(INPUT_DIFFUSION, "Diff", DIFFUSION_LAW(), 0.01f, 0.75f);
	return control;
}

std::shared_ptr<ctoot::control::FloatControl> BarrControls::createDampingControl() {
	auto control = std::make_shared<ctoot::control::FloatControl>(DAMPING, "Damp", LinearLaw::UNITY(), 0.01f, 0.f);
	return control;
}

std::shared_ptr<ctoot::control::FloatControl> BarrControls::createDecayControl() {
	auto control = std::make_shared<ctoot::control::FloatControl>(DECAY, "Decay", LinearLaw::UNITY(), 0.01f, 0.8f);
	return control;
}

std::shared_ptr<ctoot::control::FloatControl> BarrControls::createDecayDiffusionControl() {
	auto control = std::make_shared<ctoot::control::FloatControl>(DECAY_DIFFUSION, "Diff", DIFFUSION_LAW(), 0.01f, 0.7f);
	return control;
}

std::shared_ptr<ctoot::control::FloatControl> BarrControls::createSizeControl() {
	auto control = std::make_shared<ctoot::control::FloatControl>(SIZE, "Size", SIZE_LAW(), 0.01f, 1.f);
	return control;
}

void BarrControls::deriveControls() {
	preDelaySamples = derivePreDelaySamples();
	bandwidth = deriveBandwidth();
	inputDiffusion = deriveInputDiffusion();
	damping = deriveDamping();
	decay = deriveDecay();
	decayDiffusion = deriveDecayDiffusion();
	size = deriveSize();
}

int BarrControls::derivePreDelaySamples() {
	return std::max(1, (int)(preDelayControl.lock()->getValue() * 44100 / 1000)); // !!! TODO SR
}

float BarrControls::deriveBandwidth() {
	return bandwidthControl.lock()->getValue();
}

float BarrControls::deriveInputDiffusion() {
	return inputDiffusionControl.lock()->getValue();
}

float BarrControls::deriveDamping() {
	return dampingControl.lock()->getValue();
}

float BarrControls::deriveDecay() {
	return decayControl.lock()->getValue();
}

float BarrControls::deriveDecayDiffusion() {
	if (!decayDiffusionControl.lock()) return 0.5f;
	return decayDiffusionControl.lock()->getValue();
}

float BarrControls::deriveSize() {
	return sizeControl.lock()->getValue();
}

int BarrControls::getMaxPreDelaySamples() {
	return 44100 * MAX_PRE_DELAY_MS / 1000;
}

int BarrControls::getPreDelaySamples() {
	return preDelaySamples;
}

float BarrControls::getBandwidth() {
	return bandwidth;
}

float BarrControls::getInputDiffusion() {
	return inputDiffusion;
}

float BarrControls::getDamping() {
	return damping;
}

float BarrControls::getDecay() {
	return decay;
}

float BarrControls::getDecayDiffusion() {
	return decayDiffusion;
}

float BarrControls::getSize() {
	return size;
}

std::vector<std::vector<int>> BarrControls::getSizes() {
	return sizes;
}

std::vector<std::vector<int>> BarrControls::getLeftTaps() {
	return leftTaps;
}

std::vector<std::vector<int>> BarrControls::getRightTaps() {
	return rightTaps;
}

//REGISTER_TYPE(BarrControls)

