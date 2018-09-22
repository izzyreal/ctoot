#include "IzMultiBandControls.hpp"

#include "IzBandCompressorControls.hpp"
#include <audio/dynamics/CrossoverControl.hpp>
#include <audio/dynamics/DynamicsControlIds.hpp>

#include <control/FloatControl.hpp>
#include <control/LinearLaw.hpp>

#include <dsp/VolumeUtils.hpp>

using namespace ctoot::audio::dynamics::izcompressor;
using namespace ctoot::audio::dynamics;
using namespace ctoot::control;
using namespace std;

IzMultiBandControls::IzMultiBandControls()
	: MultiBandControls("IzMultiBandCompressor")
{
   add(make_shared<IzBandCompressorControls>("Low", 0));
   add(make_shared<CrossoverControl>(0, "Low Freq", 250.0f));
   add(make_shared<IzBandCompressorControls>("Lo.Mid", 30));
   add(make_shared<CrossoverControl>(1, "Mid Freq", 1000.0f));
   add(make_shared<IzBandCompressorControls>("Hi.Mid", 60));
   add(make_shared<CrossoverControl>(2, "High Freq", 4000.0f));
   add(make_shared<IzBandCompressorControls>("High", 90));

   auto igc = createInputGainControl();
   inputGainControl = igc;
   add(std::move(igc));

   auto ogc = createOutputGainControl();
   outputGainControl = ogc;
   add(std::move(ogc));
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
