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
//#include <synth/modules/oscillator/MultiWaveOscillatorControls.hpp>
//#include <synth/modules/oscillator/MultiWaveOscillatorVariables.hpp>
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
    /*
    oscillatorControls = new ctoot::synth::modules::oscillator::MultiWaveOscillatorControlsArray(int32_t(4));
    filterControls = new ctoot::synth::modules::filter::FilterControlsArray(2);
    envelopeControls = new ctoot::synth::modules::envelope::EnvelopeControlsArray(int32_t(4));
    lfoControls = new ctoot::synth::modules::oscillator::LFOControlsArray(int32_t(3));
    mixerControls = new ctoot::synth::modules::mixer::MixerControlsArray(2);
    modulationControls = new ctoot::synth::modules::mixer::ModulationMixerControlsArray(int32_t(6));
    auto widthLFOConfig = new ctoot::synth::modules::oscillator::LFOConfig();
    auto vibratoConfig = new ctoot::synth::modules::oscillator::LFOConfig();
	*/
    vibratoConfig->rateMin = 4.0f;
    vibratoConfig->rateMax = 7.0f;
    vibratoConfig->rate = 5.5f;
    vibratoConfig->deviationMax = 2.0f;
    vibratoConfig->deviation = 1.5f;

	string lfoString = "LFO";
	auto widthLabels = vector<string>{ lfoString + " 1", lfoString + " 2" };
	string widthModString = "Width Mod";
    string oscillatorString = "Oscillator";
    auto oscRow = new ctoot::control::ControlRow();
    oscillatorControls->set(0, new ctoot::synth::modules::oscillator::MultiWaveOscillatorControls(0, ::java::lang::StringBuilder().append(oscillatorString)->append(" 1")->toString(), OSC1_OFFSET, false));
   oscRow->add(static_cast< ctoot::control::Control* >((*oscillatorControls)[0]));
    modulationControls->set(0, new ctoot::synth::modules::mixer::ModulationMixerControls(0, widthModString, OSC1_MOD_OFFSET, widthLabels, true));
   oscRow->add(static_cast< ctoot::control::Control* >((*modulationControls)[0]));
    oscillatorControls->set(1, new ctoot::synth::modules::oscillator::MultiWaveOscillatorControls(1, ::java::lang::StringBuilder().append(oscillatorString)->append(" 2")->toString(), OSC2_OFFSET, false));
   oscRow->add(static_cast< ctoot::control::Control* >((*oscillatorControls)[1]));
    modulationControls->set(1, new ctoot::synth::modules::mixer::ModulationMixerControls(1, widthModString, OSC2_MOD_OFFSET, widthLabels, true));
   oscRow->add(static_cast< ctoot::control::Control* >((*modulationControls)[1]));
    oscillatorControls->set(2, new ctoot::synth::modules::oscillator::MultiWaveOscillatorControls(2, ::java::lang::StringBuilder().append(oscillatorString)->append(" 3")->toString(), OSC3_OFFSET, false));
   oscRow->add(static_cast< ctoot::control::Control* >((*oscillatorControls)[2]));
    modulationControls->set(2, new ctoot::synth::modules::mixer::ModulationMixerControls(2, widthModString, OSC3_MOD_OFFSET, widthLabels, true));
   oscRow->add(static_cast< ctoot::control::Control* >((*modulationControls)[2]));
    add(oscRow);
    string envString = "Env";
	auto cutoffLabels = vector<string>{ lfoString + " 1", lfoString + " 2", lfoString + " 1", lfoString + " 2", "Vel", "AT", "Wheel" };
    auto lpfRow = new ctoot::control::ControlRow();
    mixerControls->set(0, new ctoot::synth::modules::mixer::MixerControls(0, ::java::lang::StringBuilder().append(ctoot::misc::Localisation::getString("LPF"))->append(" ")
        ->append(oscillatorString)
        ->append(" ")
        ->append(ctoot::misc::Localisation::getString("Mix"))->toString(), LPFMIX_OFFSET, int32_t(3)));
    lpfRow->add(static_cast< ctoot::control::Control* >((*mixerControls)[0]));
    filterControls->set(0, new ctoot::synth::modules::filter::MoogFilterControls(0, ::java::lang::StringBuilder().append(ctoot::misc::Localisation::getString("Low.Pass"))->append(" ")
        ->append(ctoot::misc::Localisation::getString("Filter"))->toString(), LPF_OFFSET));
    lpfRow->add(static_cast< ctoot::control::Control* >((*filterControls)[0]));
    modulationControls->set(int32_t(3), new ctoot::synth::modules::mixer::ModulationMixerControls(int32_t(3), ::java::lang::StringBuilder().append(ctoot::misc::Localisation::getString("Cutoff"))->append(" ")
        ->append(ctoot::misc::Localisation::getString("Mod"))->toString(), LPF_MOD_OFFSET, cutoffLabels, true, int32_t(64), u"semitones"));
    lpfRow->add(static_cast< ctoot::control::Control* >((*modulationControls)[int32_t(3)]));
    add(lpfRow);
    auto svfRow = new ctoot::control::ControlRow();
    mixerControls->set(1, new ctoot::synth::modules::mixer::MixerControls(1, ::java::lang::StringBuilder().append(ctoot::misc::Localisation::getString("SVF"))->append(" ")
        ->append(oscillatorString)
        ->append(" ")
        ->append(ctoot::misc::Localisation::getString("Mix"))->toString(), SVFMIX_OFFSET, int32_t(3)));
    npc(svfRow)->add(static_cast< ctoot::control::Control* >((*mixerControls)[1]));
    filterControls->set(1, new ctoot::synth::modules::filter::StateVariableFilterControls(0, ::java::lang::StringBuilder().append(ctoot::misc::Localisation::getString("State.Variable"))->append(" ")
        ->append(ctoot::misc::Localisation::getString("Filter"))->toString(), SVF_OFFSET));
    npc(svfRow)->add(static_cast< ctoot::control::Control* >((*filterControls)[1]));
    modulationControls->set(int32_t(4), new ctoot::synth::modules::mixer::ModulationMixerControls(int32_t(4), ::java::lang::StringBuilder().append(ctoot::misc::Localisation::getString("Cutoff"))->append(" ")
        ->append(ctoot::misc::Localisation::getString("Mod"))->toString(), SVF_MOD_OFFSET, cutoffLabels, true, int32_t(64), u"semitones"));
    npc(svfRow)->add(static_cast< ctoot::control::Control* >((*modulationControls)[int32_t(4)]));
    add(svfRow);
    auto envRow = new ctoot::control::ControlRow();
    envelopeControls->set(1, new ctoot::synth::modules::envelope::EnvelopeControls(1, ::java::lang::StringBuilder().append(ctoot::misc::Localisation::getString("Envelope"))->append(" 1")->toString(), ENV1_OFFSET));
    envRow->add(static_cast< ctoot::control::Control* >((*envelopeControls)[1]));
    envelopeControls->set(2, new ctoot::synth::modules::envelope::EnvelopeControls(2, ::java::lang::StringBuilder().append(ctoot::misc::Localisation::getString("Envelope"))->append(" 2")->toString(), ENV2_OFFSET));
    envRow->add(static_cast< ctoot::control::Control* >((*envelopeControls)[2]));
    envelopeControls->set(0, new ctoot::synth::modules::envelope::EnvelopeControls(0, ::java::lang::StringBuilder().append(ctoot::misc::Localisation::getString("Amplifier"))->append(" ")
        ->append(ctoot::misc::Localisation::getString("Envelope"))->toString(), AMPENV_OFFSET));
    envRow->add(static_cast< ctoot::control::Control* >((*envelopeControls)[0]));
    amplifierControls = new ctoot::synth::modules::amplifier::AmplifierControls(0, ctoot::misc::Localisation::getString("Amplifier"), AMP_OFFSET);
    envRow->add(static_cast< ctoot::control::Control* >(amplifierControls));
    add(envRow);
	
	auto vibLabels = vector<string>{ "Env", "AT", "Wheel" };

    auto lfoRow = new ctoot::control::ControlRow();
    lfoControls->set(1, new ctoot::synth::modules::oscillator::LFOControls(1, ::java::lang::StringBuilder().append(lfoString)->append(" 1")->toString(), LFO1_OFFSET, widthLFOConfig));
    lfoRow->add(static_cast< ctoot::control::Control* >((*lfoControls)[1]));
    lfoControls->set(2, new ctoot::synth::modules::oscillator::LFOControls(2, ::java::lang::StringBuilder().append(lfoString)->append(" 2")->toString(), LFO2_OFFSET, widthLFOConfig));
    lfoRow->add(static_cast< ctoot::control::Control* >((*lfoControls)[2]));
    lfoControls->set(0, new ctoot::synth::modules::oscillator::LFOControls(0, ctoot::misc::Localisation::getString("Vibrato"), LFOVIB_OFFSET, vibratoConfig));
    lfoRow->add(static_cast< ctoot::control::Control* >((*lfoControls)[0]));
    envelopeControls->set(int32_t(3), new ctoot::synth::modules::envelope::EnvelopeControls(int32_t(3), ::java::lang::StringBuilder().append(ctoot::misc::Localisation::getString("Vibrato"))->append(" ")
        ->append(ctoot::misc::Localisation::getString("Envelope"))->toString(), VIBENV_OFFSET, u"D", 5.0f));
    lfoRow->add(static_cast< ctoot::control::Control* >((*envelopeControls)[int32_t(3)]));
    modulationControls->set(int32_t(5), new ctoot::synth::modules::mixer::ModulationMixerControls(int32_t(5), ::java::lang::StringBuilder().append(ctoot::misc::Localisation::getString("Vibrato"))->append(" ")
        ->append(ctoot::misc::Localisation::getString("Mod"))->toString(), VIB_MOD_OFFSET, vibLabels, false));
    lfoRow->add(static_cast< ctoot::control::Control* >((*modulationControls)[int32_t(5)]));
    add(lfoRow);
}

 ctoot::synth::modules::oscillator::MultiWaveOscillatorVariables* ValorSynthControls::getOscillatorVariables(int32_t instance)
{
    return oscillatorControls[instance];
}

 ctoot::synth::modules::filter::FilterVariables* ValorSynthControls::getFilterVariables(int32_t instance)
{
    return filterControls[instance];
}

 ctoot::synth::modules::envelope::EnvelopeVariables* ValorSynthControls::getEnvelopeVariables(int32_t instance)
{
    return envelopeControls[instance];
}

 ctoot::synth::modules::amplifier::AmplifierVariables* ValorSynthControls::getAmplifierVariables()
{
    return amplifierControls;
}

 ctoot::synth::modules::oscillator::LFOControls* ValorSynthControls::getLFOVariables(int32_t instance)
{
    return lfoControls[instance];
}

 ctoot::synth::modules::mixer::MixerVariables* ValorSynthControls::getMixerVariables(int32_t instance)
{
    return mixerControls[instance];
}

 ctoot::synth::modules::mixer::ModulationMixerVariables* ValorSynthControls::getModulationMixerVariables(int32_t instance)
{
    return modulationControls[instance];
}
