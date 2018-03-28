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
//#include <synth/modules/oscillator/MultiWaveOscillatorVariables.hpp>
//#include <synth/modules/oscillator/MultiWaves.hpp>

using namespace ctoot::synth::channels::valor;

ValorSynthChannel::ValorSynthChannel(ValorSynthControls* controls)
	: ctoot::synth::PolyphonicSynthChannel(controls->getName())
{
    oscillator1Vars = controls->getOscillatorVariables(1 - 1);
    oscillator2Vars = controls->getOscillatorVariables(2 - 1);
    oscillator3Vars = controls->getOscillatorVariables(3 - 1);
    envelopeAVars = controls->getEnvelopeVariables(0);
    envelope1Vars = controls->getEnvelopeVariables(1);
    envelope2Vars = controls->getEnvelopeVariables(2);
    envelopeVVars = controls->getEnvelopeVariables(3);
    lpFilterVars = controls->getFilterVariables(0);
    svFilterVars = controls->getFilterVariables(1);
    amplifierVars = controls->getAmplifierVariables();
    vibratoVars = controls->getLFOVariables(0);
    lfo1Vars = controls->getLFOVariables(1);
    lfo2Vars = controls->getLFOVariables(2);
    lpFilterMixerVars = controls->getMixerVariables(0);
    svFilterMixerVars = controls->getMixerVariables(1);
    osc1WidthModMixer = controls->getModulationMixerVariables(0);
    osc2WidthModMixer = controls->getModulationMixerVariables(1);
    osc3WidthModMixer = controls->getModulationMixerVariables(2);
    lpfCutoffModMixer = controls->getModulationMixerVariables(3);
    svfCutoffModMixer = controls->getModulationMixerVariables(4);
    vibModMixer = controls->getModulationMixerVariables(5);
    createVoice(42, 0, 44100);
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
