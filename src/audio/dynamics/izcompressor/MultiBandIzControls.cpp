#include <audio/dynamics/izcompressor/MultiBandIzControls.hpp>

#include <audio/dynamics/izcompressor/IzBandCompressorControls.hpp>
#include <audio/dynamics/CrossoverControl.hpp>
#include <audio/dynamics/DynamicsControlIds.hpp>

#include <control/FloatControl.hpp>
#include <control/LinearLaw.hpp>

#include <dsp/VolumeUtils.hpp>

using namespace ctoot::audio::dynamics::izcompressor;
using namespace ctoot::audio::dynamics;
using namespace ctoot::control;
using namespace std;

MultiBandIzControls::MultiBandIzControls()
	: MultiBandControls("MultiBandIzCompressor")
{
   add(make_shared<IzBandCompressorControls>("Low"));
   add(make_shared<CrossoverControl>("Low Freq", 250.0f));
   add(make_shared<IzBandCompressorControls>("Lo.Mid"));
   add(make_shared<CrossoverControl>("Mid Freq", 1000.0f));
   add(make_shared<IzBandCompressorControls>("Hi.Mid"));
   add(make_shared<CrossoverControl>("High Freq", 4000.0f));
   add(make_shared<IzBandCompressorControls>("High"));
   auto igc = createInputGainControl();
   inputGainControl = igc;
   add(std::move(igc));
}

weak_ptr<ctoot::control::ControlLaw> MultiBandIzControls::INPUT_GAIN_LAW()
{
	static auto res = make_shared<LinearLaw>(-24.0f, 24.0f, "dB");
	return res;
}

shared_ptr<ctoot::control::FloatControl> MultiBandIzControls::createInputGainControl()
{
	return make_shared<ctoot::control::FloatControl>(DynamicsControlIds::INPUT_GAIN + 0, "Input Gain", INPUT_GAIN_LAW(), 1.0f, 0);
}

void MultiBandIzControls::deriveInputGain() {
	if (!inputGainControl.lock()) return;
	inputGain = static_cast<float>(ctoot::dsp::VolumeUtils::log2lin(inputGainControl.lock()->getValue()));
}

float MultiBandIzControls::getInputGain() {
	deriveInputGain();
	return inputGain;
}
