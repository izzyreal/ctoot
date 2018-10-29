#include "IzMultiBandControls.hpp"

#include "IzBandCompressorControls.hpp"
#include <audio/dynamics/CrossoverControl.hpp>
#include <audio/dynamics/DynamicsControlIds.hpp>
#include <audio/dynamics/izcompressor/LinkControl.hpp>

#include <control/FloatControl.hpp>
#include <control/LinearLaw.hpp>
#include <control/IntegerLaw.hpp>

#include <dsp/VolumeUtils.hpp>

using namespace ctoot::audio::dynamics::izcompressor;
using namespace ctoot::audio::dynamics;
using namespace ctoot::control;
using namespace std;

IzMultiBandControls::IzMultiBandControls()
	: MultiBandControls("IzMultiBandCompressor")
{
	vector<weak_ptr<IzBandCompressorControls>> controls;
	auto c1 = make_shared<IzBandCompressorControls>("Low", 0);
	controls.push_back(c1);
	add(std::move(c1));
	add(make_shared<CrossoverControl>(0, "Low Freq", 250.0f));
	auto c2 = make_shared<IzBandCompressorControls>("Lo.Mid", 25);
	controls.push_back(c2);
	add(std::move(c2));
	add(make_shared<CrossoverControl>(1, "Mid Freq", 1000.0f));
	auto c3 = make_shared<IzBandCompressorControls>("Hi.Mid", 50);
	controls.push_back(c3);
	add(std::move(c3));
	add(make_shared<CrossoverControl>(2, "High Freq", 4000.0f));
	auto c4 = make_shared<IzBandCompressorControls>("High", 75);
	controls.push_back(c4);
	add(std::move(c4));

	auto igc = createInputGainControl();
	inputGainControl = igc;
	add(std::move(igc));

	auto ogc = createOutputGainControl();
	outputGainControl = ogc;
	add(std::move(ogc));

	auto lc = createLinkControl(controls);
	linkControl = lc;
	add(std::move(lc));
}

weak_ptr<ctoot::control::ControlLaw> IzMultiBandControls::INPUT_GAIN_LAW()
{
	static auto res = make_shared<LinearLaw>(-24.0f, 24.0f, "dB");
	return res;
}

shared_ptr<ctoot::control::FloatControl> IzMultiBandControls::createInputGainControl()
{
	return make_shared<ctoot::control::FloatControl>(DynamicsControlIds::MASTER_INPUT_GAIN, "Master Input Gain", INPUT_GAIN_LAW(), 1.0f, 0);
}

void IzMultiBandControls::deriveInputGain() {
	if (!inputGainControl.lock()) return;
	inputGain = static_cast<float>(ctoot::dsp::VolumeUtils::log2lin(inputGainControl.lock()->getValue()));
}

float IzMultiBandControls::getInputGain() {
	deriveInputGain();
	return inputGain;
}

weak_ptr<IntegerLaw> IzMultiBandControls::LINK_LAW()
{
	static auto res = make_shared<IntegerLaw>(0, 4, "Band");
	return res;
}

shared_ptr<LinkControl> IzMultiBandControls::createLinkControl(vector<weak_ptr<IzBandCompressorControls>> controls) {
	return make_shared<LinkControl>(DynamicsControlIds::LINK, "Link", LINK_LAW(), controls);
}

weak_ptr<ctoot::control::ControlLaw> IzMultiBandControls::OUTPUT_GAIN_LAW()
{
	static auto res = make_shared<LinearLaw>(-24.0f, 24.0f, "dB");
	return res;
}

shared_ptr<ctoot::control::FloatControl> IzMultiBandControls::createOutputGainControl()
{
	return make_shared<ctoot::control::FloatControl>(DynamicsControlIds::MASTER_OUTPUT_GAIN, "Master Output Gain", OUTPUT_GAIN_LAW(), 1.0f, 0);
}

void IzMultiBandControls::deriveOutputGain() {
	if (!outputGainControl.lock()) return;
	outputGain = static_cast<float>(ctoot::dsp::VolumeUtils::log2lin(outputGainControl.lock()->getValue()));
}

float IzMultiBandControls::getOutputGain() {
	deriveOutputGain();
	return outputGain;
}
