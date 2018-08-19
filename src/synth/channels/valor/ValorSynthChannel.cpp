#include <synth/channels/valor/ValorSynthChannel.hpp>

#include <synth/channels/valor/Example2Voice.hpp>
#include <synth/channels/valor/ValorSynthControls.hpp>
#include <synth/modules/amplifier/AmplifierVariables.hpp>
#include <synth/modules/envelope/EnvelopeVariables.hpp>
#include <synth/modules/filter/FilterVariables.hpp>
#include <synth/modules/filter/StateVariableFilterVariables.hpp>
#include <synth/modules/mixer/MixerVariables.hpp>
#include <synth/modules/mixer/ModulationMixerVariables.hpp>
#include <synth/modules/oscillator/LFOControls.hpp>
#include <synth/modules/oscillator/MultiWaveOscillatorVariables.hpp>
#include <synth/modules/oscillator/MultiWaves.hpp>

using namespace ctoot::synth::channels::valor;
using namespace std;

ValorSynthChannel::ValorSynthChannel(ValorSynthControls* controls)
	: ctoot::synth::PolyphonicSynthChannel(controls->getName())
{
	MLOG("ValorSynthChannel constructor");
	oscillator1Vars = controls->getOscillatorVariables(1 - 1).lock().get();
	oscillator2Vars = controls->getOscillatorVariables(2 - 1).lock().get();
	oscillator3Vars = controls->getOscillatorVariables(3 - 1).lock().get();
	envelopeAVars = controls->getEnvelopeVariables(0).lock().get();
	envelope1Vars = controls->getEnvelopeVariables(1).lock().get();
	envelope2Vars = controls->getEnvelopeVariables(2).lock().get();
	envelopeVVars = controls->getEnvelopeVariables(3).lock().get();
	lpFilterVars = controls->getFilterVariables(0).lock().get();
	svFilterVars = dynamic_pointer_cast<ctoot::synth::modules::filter::StateVariableFilterVariables>(controls->getFilterVariables(1).lock()).get();
	amplifierVars = controls->getAmplifierVariables().lock().get();
	vibratoVars = controls->getLFOVariables(0).lock().get();
	lfo1Vars = controls->getLFOVariables(1).lock().get();
	lfo2Vars = controls->getLFOVariables(2).lock().get();
	lpFilterMixerVars = controls->getMixerVariables(0).lock().get();
	svFilterMixerVars = controls->getMixerVariables(1).lock().get();
	osc1WidthModMixer = controls->getModulationMixerVariables(0).lock().get();
	osc2WidthModMixer = controls->getModulationMixerVariables(1).lock().get();
	osc3WidthModMixer = controls->getModulationMixerVariables(2).lock().get();
	lpfCutoffModMixer = controls->getModulationMixerVariables(3).lock().get();
	svfCutoffModMixer = controls->getModulationMixerVariables(4).lock().get();
	vibModMixer = controls->getModulationMixerVariables(5).lock().get();
}

void ValorSynthChannel::setSampleRate(int32_t rate)
{
	ctoot::synth::PolyphonicSynthChannel::setSampleRate(rate);
    envelopeAVars->setSampleRate(rate);
    envelope1Vars->setSampleRate(rate);
    envelope2Vars->setSampleRate(rate);
    envelopeVVars->setSampleRate(rate);
    lpFilterVars->setSampleRate(rate);
    svFilterVars->setSampleRate(rate);
}

 ctoot::synth::PolyphonicSynthChannelVoice* ctoot::synth::channels::valor::ValorSynthChannel::createVoice(int32_t pitch, int32_t velocity, int32_t sampleRate)
{
    return new Example2Voice(this, pitch, velocity, sampleRate);
}
