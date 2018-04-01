#include <synth/channels/valor/ValorSynthControls.hpp>

#include <control/ControlRow.hpp>
#include <control/CompoundControl.hpp>
#include <control/Control.hpp>
//#include <misc/Localisation.hpp>
#include <synth/id/TootSynthControlsId.hpp>
#include <synth/modules/amplifier/AmplifierControls.hpp>
#include <synth/modules/envelope/EnvelopeControls.hpp>
#include <synth/modules/envelope/EnvelopeVariables.hpp>
#include <synth/modules/filter/FilterControls.hpp>
#include <synth/modules/filter/FilterVariables.hpp>
#include <synth/modules/filter/MoogFilterControls.hpp>
#include <synth/modules/filter/StateVariableFilterControls.hpp>
#include <synth/modules/mixer/SynthMixerControls.hpp>
#include <synth/modules/mixer/MixerVariables.hpp>
#include <synth/modules/mixer/ModulationMixerControls.hpp>
#include <synth/modules/mixer/ModulationMixerVariables.hpp>
#include <synth/modules/oscillator/LFOConfig.hpp>
#include <synth/modules/oscillator/LFOControls.hpp>
#include <synth/modules/oscillator/LFOVariables.hpp>
#include <synth/modules/oscillator/MultiWaveOscillatorControls.hpp>
#include <synth/modules/oscillator/MultiWaveOscillatorVariables.hpp>
#include <synth/modules/oscillator/OscillatorVariables.hpp>

using namespace ctoot::synth::channels::valor;
using namespace std;

std::string ValorSynthControls::NAME = "Valor";

constexpr int32_t ValorSynthControls::OSC1_OFFSET;
constexpr int32_t ValorSynthControls::OSC2_OFFSET;
constexpr int32_t ValorSynthControls::OSC3_OFFSET;
constexpr int32_t ValorSynthControls::LFOVIB_OFFSET;
constexpr int32_t ValorSynthControls::VIB_MOD_OFFSET;
constexpr int32_t ValorSynthControls::LPF_OFFSET;
constexpr int32_t ValorSynthControls::OSC3_MOD_OFFSET;
constexpr int32_t ValorSynthControls::LPFMIX_OFFSET;
constexpr int32_t ValorSynthControls::SVFMIX_OFFSET;
constexpr int32_t ValorSynthControls::SVF_OFFSET;
constexpr int32_t ValorSynthControls::AMP_OFFSET;
constexpr int32_t ValorSynthControls::VIBENV_OFFSET;
constexpr int32_t ValorSynthControls::AMPENV_OFFSET;
constexpr int32_t ValorSynthControls::ENV1_OFFSET;
constexpr int32_t ValorSynthControls::ENV2_OFFSET;
constexpr int32_t ValorSynthControls::LPF_MOD_OFFSET;
constexpr int32_t ValorSynthControls::SVF_MOD_OFFSET;
constexpr int32_t ValorSynthControls::LFO1_OFFSET;
constexpr int32_t ValorSynthControls::OSC1_MOD_OFFSET;
constexpr int32_t ValorSynthControls::LFO2_OFFSET;
constexpr int32_t ValorSynthControls::OSC2_MOD_OFFSET;

ValorSynthControls::ValorSynthControls()
	: ctoot::synth::SynthChannelControls(ctoot::synth::id::TootSynthControlsId::VALOR_CHANNEL_ID, NAME)
{
	oscillatorControls = vector<weak_ptr<ctoot::synth::modules::oscillator::MultiWaveOscillatorControls>>(4);
	filterControls = vector<weak_ptr<ctoot::synth::modules::filter::FilterControls>>(2);
	envelopeControls = vector<weak_ptr<ctoot::synth::modules::envelope::EnvelopeControls>>(4);
	lfoControls = vector<weak_ptr<ctoot::synth::modules::oscillator::LFOControls>>(3);
	mixerControls = vector<weak_ptr<ctoot::synth::modules::mixer::MixerControls>>(2);
	modulationControls = vector<weak_ptr<ctoot::synth::modules::mixer::ModulationMixerControls>>(6);
	auto widthLFOConfig = new ctoot::synth::modules::oscillator::LFOConfig();
	auto vibratoConfig = new ctoot::synth::modules::oscillator::LFOConfig();
	vibratoConfig->rateMin = 4.0f;
	vibratoConfig->rateMax = 7.0f;
	vibratoConfig->rate = 5.5f;
	vibratoConfig->deviationMax = 2.0f;
	vibratoConfig->deviation = 1.5f;

	string lfoString = "LFO";
	auto widthLabels = vector<string>{ lfoString + " 1", lfoString + " 2" };
	string widthModString = "Width Mod";
	string oscillatorString = "Oscillator";
	auto oscRow = make_shared<ctoot::control::ControlRow>();

	auto oc0 = make_shared<ctoot::synth::modules::oscillator::MultiWaveOscillatorControls>(0, oscillatorString + " 1", OSC1_OFFSET, false);
	oscillatorControls[0] = oc0;
	oscRow->add(std::move(oc0));

	auto mc0 = make_shared<ctoot::synth::modules::mixer::ModulationMixerControls>(0, widthModString, OSC1_MOD_OFFSET, widthLabels, true);
	modulationControls[0] = mc0;
	oscRow->add(std::move(mc0));

	auto oc1 = make_shared<ctoot::synth::modules::oscillator::MultiWaveOscillatorControls>(1, oscillatorString + " 2", OSC2_OFFSET, false);
	oscillatorControls[1] = oc1;
	oscRow->add(std::move(oc1));

	auto mc1 = make_shared<ctoot::synth::modules::mixer::ModulationMixerControls>(1, widthModString, OSC2_MOD_OFFSET, widthLabels, true);
	modulationControls[1] = mc1;
	oscRow->add(std::move(mc1));

	auto oc2 = make_shared<ctoot::synth::modules::oscillator::MultiWaveOscillatorControls>(2, oscillatorString + " 3", OSC3_OFFSET, false);
	oscillatorControls[2] = oc2;
	oscRow->add(std::move(oc2));

	auto mc2 = make_shared<ctoot::synth::modules::mixer::ModulationMixerControls>(2, widthModString, OSC3_MOD_OFFSET, widthLabels, true);
	modulationControls[2] = mc2;
	oscRow->add(std::move(mc2));
	add(std::move(oscRow));

	string envString = "Env";
	auto cutoffLabels = vector<string>{ lfoString + " 1", lfoString + " 2", lfoString + " 1", lfoString + " 2", "Vel", "AT", "Wheel" };
	auto lpfRow = make_shared<ctoot::control::ControlRow>();

	auto mxc0 = make_shared<ctoot::synth::modules::mixer::MixerControls>(0, "LPF " + oscillatorString + " Mix", LPFMIX_OFFSET, 3);
	mixerControls[0] = mxc0;
	lpfRow->add(std::move(mxc0));

	auto fc0 = make_shared<ctoot::synth::modules::filter::MoogFilterControls>(0, "Low.Pass Filter", LPF_OFFSET);
	filterControls[0] = fc0;
	lpfRow->add(std::move(fc0));

	auto mc3 = make_shared<ctoot::synth::modules::mixer::ModulationMixerControls>(3, "Cutoff Mod", LPF_MOD_OFFSET, cutoffLabels, true, 64, "semitones");
	modulationControls[3] = mc3;
	lpfRow->add(std::move(mc3));

	add(std::move(lpfRow));

	auto svfRow = make_shared<ctoot::control::ControlRow>();
	auto mxc1 = make_shared<ctoot::synth::modules::mixer::MixerControls>(1, "SVF " + oscillatorString + " Mix", SVFMIX_OFFSET, 3);
	mixerControls[1] = mxc1;
	svfRow->add(std::move(mxc1));

	auto fc1 = make_shared<ctoot::synth::modules::filter::StateVariableFilterControls>(0, "State.Variable Filter", SVF_OFFSET);
	filterControls[1] = fc1;
	svfRow->add(std::move(fc1));

	auto m4 = make_shared<ctoot::synth::modules::mixer::ModulationMixerControls>(4, "Cutoff Mod", SVF_MOD_OFFSET, cutoffLabels, true, 64, "semitones");
	modulationControls[4] = m4;
	svfRow->add(std::move(m4));

	add(std::move(svfRow));

	auto envRow = make_shared<ctoot::control::ControlRow>();

	auto ec1 = make_shared<ctoot::synth::modules::envelope::EnvelopeControls>(1, "Envelope 1", ENV1_OFFSET);
	envelopeControls[1] = ec1;
	envRow->add(std::move(ec1));

	auto ec2 = make_shared<ctoot::synth::modules::envelope::EnvelopeControls>(2, "Envelope 2", ENV2_OFFSET);
	envelopeControls[2] = ec2;
	envRow->add(std::move(ec2));

	auto ec0 = make_shared<ctoot::synth::modules::envelope::EnvelopeControls>(0, "Amplifier Envelope", AMPENV_OFFSET);
	envelopeControls[0] = ec0;
	envRow->add(std::move(ec0));

	auto ac = make_shared<ctoot::synth::modules::amplifier::AmplifierControls>(0, "Amplifier", AMP_OFFSET);
	amplifierControls = ac;
	envRow->add(std::move(ac));

	add(std::move(envRow));

	auto vibLabels = vector<string>{ "Env", "AT", "Wheel" };

	auto lfoRow = make_shared<ctoot::control::ControlRow>();

	auto lc1 = make_shared<ctoot::synth::modules::oscillator::LFOControls>(1, lfoString + " 1", LFO1_OFFSET, widthLFOConfig);
	lfoControls[1] = lc1;
	lfoRow->add(std::move(lc1));

	auto lc2 = make_shared<ctoot::synth::modules::oscillator::LFOControls>(2, lfoString + " 2", LFO2_OFFSET, widthLFOConfig);
	lfoControls[2] = lc2;
	lfoRow->add(std::move(lc2));

	auto lc0 = make_shared<ctoot::synth::modules::oscillator::LFOControls>(0, "Vibrato", LFOVIB_OFFSET, vibratoConfig);
	lfoControls[0] = lc0;
	lfoRow->add(std::move(lc0));

	auto ec3 = make_shared<ctoot::synth::modules::envelope::EnvelopeControls>(3, "Vibrato Envelope", VIBENV_OFFSET, "D", 5.0f);
	envelopeControls[3] = ec3;
	lfoRow->add(std::move(ec3));

	auto mc5 = make_shared<ctoot::synth::modules::mixer::ModulationMixerControls>(5, "Vibrato Mod", VIB_MOD_OFFSET, vibLabels, false);
	modulationControls[5] = mc5;
	lfoRow->add(std::move(mc5));

	add(std::move(lfoRow));
}

 weak_ptr<ctoot::synth::modules::oscillator::MultiWaveOscillatorVariables> ValorSynthControls::getOscillatorVariables(int32_t instance)
{
    return oscillatorControls[instance];
}

 weak_ptr<ctoot::synth::modules::filter::FilterVariables> ValorSynthControls::getFilterVariables(int32_t instance)
{
    return filterControls[instance];
}

 weak_ptr<ctoot::synth::modules::envelope::EnvelopeVariables> ValorSynthControls::getEnvelopeVariables(int32_t instance)
{
    return envelopeControls[instance];
}

 weak_ptr<ctoot::synth::modules::amplifier::AmplifierVariables> ValorSynthControls::getAmplifierVariables()
{
    return amplifierControls;
}

 weak_ptr<ctoot::synth::modules::oscillator::LFOControls> ValorSynthControls::getLFOVariables(int32_t instance)
{
    return lfoControls[instance];
}

 weak_ptr<ctoot::synth::modules::mixer::MixerVariables> ValorSynthControls::getMixerVariables(int32_t instance)
{
    return mixerControls[instance];
}

 weak_ptr<ctoot::synth::modules::mixer::ModulationMixerVariables> ValorSynthControls::getModulationMixerVariables(int32_t instance)
{
    return modulationControls[instance];
}
