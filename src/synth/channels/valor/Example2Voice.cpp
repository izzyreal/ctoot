#include <synth/channels/valor/Example2Voice.hpp>

#include <midi/misc/Controller.hpp>
#include <synth/SynthChannel.hpp>
#include <synth/channels/valor/ValorSynthChannel.hpp>
#include <synth/modules/amplifier/AmplifierVariables.hpp>
#include <synth/modules/envelope/EnvelopeGenerator.hpp>
#include <synth/modules/filter/MoogFilter2.hpp>
#include <synth/modules/filter/StateVariableFilter.hpp>
#include <synth/modules/mixer/MixerVariables.hpp>
#include <synth/modules/mixer/ModulationMixerVariables.hpp>
#include <synth/modules/oscillator/LFO.hpp>
//#include <synth/modules/oscillator/MultiWaveOscillator.hpp>
#include <synth/modules/oscillator/OscillatorControl.hpp>

using namespace ctoot::synth::channels::valor;

Example2Voice::Example2Voice(int32_t pitch, int32_t velocity, int32_t sampleRate)
{
    super::ctor(pitch, velocity);
    init();
    lfo1 = new ctoot::synth::modules::oscillator::LFO(ValorSynthChannel_this->lfo1Vars, static_cast< float >((-::java::lang::Math::PI / int32_t(2))));
    lfo2 = new ctoot::synth::modules::oscillator::LFO(ValorSynthChannel_this->lfo2Vars, static_cast< float >((-::java::lang::Math::PI / int32_t(2))));
    oscillator1 = new ctoot::synth::modules::oscillator::MultiWaveOscillator(ValorSynthChannel_this, ValorSynthChannel_this->oscillator1Vars, frequency);
    oscillator2 = new ctoot::synth::modules::oscillator::MultiWaveOscillator(ValorSynthChannel_this, ValorSynthChannel_this->oscillator2Vars, frequency);
    oscillator3 = new ctoot::synth::modules::oscillator::MultiWaveOscillator(ValorSynthChannel_this, ValorSynthChannel_this->oscillator3Vars, frequency);
    envelopeA = new ctoot::synth::modules::envelope::EnvelopeGenerator(ValorSynthChannel_this->envelopeAVars);
    npc(envelopeA)->trigger();
    envelope1 = new ctoot::synth::modules::envelope::EnvelopeGenerator(ValorSynthChannel_this->envelope1Vars);
    npc(envelope1)->trigger();
    envelope2 = new ctoot::synth::modules::envelope::EnvelopeGenerator(ValorSynthChannel_this->envelope2Vars);
    npc(envelope2)->trigger();
    lfoVib = new ctoot::synth::modules::oscillator::LFO(ValorSynthChannel_this->vibratoVars);
    envelopeVib = new ctoot::synth::modules::envelope::EnvelopeGenerator(ValorSynthChannel_this->envelopeVVars);
    npc(envelopeVib)->trigger();
    lpFilter = new ctoot::synth::modules::filter::MoogFilter2(ValorSynthChannel_this->lpFilterVars);
    svFilter = new ctoot::synth::modules::filter::StateVariableFilter(ValorSynthChannel_this->svFilterVars);
    oscControl = new ctoot::synth::modules::oscillator::OscillatorControl();
    auto ampTracking = npc(ValorSynthChannel_this->amplifierVars)->getVelocityTrack();
    ampT = velocity == 0 ? 0.0f : (int32_t(1) - ampTracking * (int32_t(1) - amplitude));
    setSampleRate(sampleRate);
}

void channels::valor::ValorSynthChannel_Example2Voice::setSampleRate(int32_t rate)
{
    npc(oscillator1)->setSampleRate(rate);
    npc(oscillator2)->setSampleRate(rate);
    npc(oscillator3)->setSampleRate(rate);
    npc(lfoVib)->setSampleRate(rate);
    npc(lfo1)->setSampleRate(rate);
    npc(lfo2)->setSampleRate(rate);
}

bool ctoot::synth::channels::valor::ValorSynthChannel_Example2Voice::mix(ctoot::audio::core::AudioBuffer* buffer)
{
    npc(lfoVib)->update();
    npc(lfo1)->update();
    npc(lfo2)->update();
    npc(oscillator1)->update();
    lpfOsc1Level = npc(ValorSynthChannel_this->lpFilterMixerVars)->getLevel(0);
    lpfOsc2Level = npc(ValorSynthChannel_this->lpFilterMixerVars)->getLevel(1);
    lpfOsc3Level = npc(ValorSynthChannel_this->lpFilterMixerVars)->getLevel(2);
    svfOsc1Level = npc(ValorSynthChannel_this->svFilterMixerVars)->getLevel(0);
    svfOsc2Level = npc(ValorSynthChannel_this->svFilterMixerVars)->getLevel(1);
    svfOsc3Level = npc(ValorSynthChannel_this->svFilterMixerVars)->getLevel(2);
    osc2Enabled = lpfOsc2Level + svfOsc2Level > 0.01f;
    if(osc2Enabled)
        npc(oscillator2)->update();

    osc3Enabled = lpfOsc3Level + svfOsc3Level > 0.01f;
    if(osc3Enabled)
        npc(oscillator3)->update();

    osc1WidthModDepths = npc(ValorSynthChannel_this->osc1WidthModMixer)->getDepths();
    osc2WidthModDepths = npc(ValorSynthChannel_this->osc2WidthModMixer)->getDepths();
    osc3WidthModDepths = npc(ValorSynthChannel_this->osc3WidthModMixer)->getDepths();
    lpfCutoffModDepths = npc(ValorSynthChannel_this->lpfCutoffModMixer)->getDepths();
    svfCutoffModDepths = npc(ValorSynthChannel_this->svfCutoffModMixer)->getDepths();
    vibModDepths = npc(ValorSynthChannel_this->vibModMixer)->getDepths();
    (*modSamples)[int32_t(4)] = amplitude;
    (*modSamples)[int32_t(5)] = ValorSynthChannel_this->getChannelPressure() / int32_t(128);
    (*modSamples)[int32_t(6)] = ValorSynthChannel_this->getController(ctoot::midi::misc::Controller::MODULATION) / int32_t(128);
    vibModPre = (*modSamples)[int32_t(5)] * (*vibModDepths)[int32_t(1)] + (*modSamples)[int32_t(6)] * (*vibModDepths)[int32_t(2)];
    lpfEnabled = lpfOsc1Level + lpfOsc2Level + lpfOsc3Level > 0.01f;
    if(lpfEnabled) {
        flpstatic = modulation(4, 3, lpfCutoffModDepths);
        flpstatic += npc(lpFilter)->update();
    }
    svfEnabled = svfOsc1Level + svfOsc2Level + svfOsc3Level > 0.01f;
    if(svfEnabled) {
        fsvstatic = modulation(4, 3, svfCutoffModDepths);
        fsvstatic += npc(svFilter)->update();
    }
    ampLevel = npc(ValorSynthChannel_this->amplifierVars)->getLevel() * ampT;
    return super::mix(buffer);
}

float ctoot::synth::channels::valor::ValorSynthChannel_Example2Voice::getSample()
{
    auto sample = 0.0f;
    auto s2 = 0.0f;
    auto s3 = 0.0f;
    (*modSamples)[int32_t(0)] = (1.0f + npc(lfo1)->getSample()) / int32_t(2);
    (*modSamples)[int32_t(1)] = (1.0f + npc(lfo2)->getSample()) / int32_t(2);
    (*modSamples)[int32_t(2)] = npc(envelope1)->getEnvelope(release_);
    (*modSamples)[int32_t(3)] = npc(envelope2)->getEnvelope(release_);
    auto vibMod = vibModPre + npc(envelopeVib)->getEnvelope(release_) * (*vibModDepths)[int32_t(0)];
    vibMod *= npc(lfoVib)->getSample() / int32_t(50);
    vibMod += 1.0f;
    auto s1 = npc(oscillator1)->getSample(vibMod, modulation(0, 2, osc1WidthModDepths), oscControl);
    if(osc2Enabled) {
        s2 = npc(oscillator2)->getSample(vibMod, modulation(0, 2, osc2WidthModDepths), oscControl);
    }
    if(osc3Enabled) {
        s3 = npc(oscillator3)->getSample(vibMod, modulation(0, 2, osc3WidthModDepths), oscControl);
    }
    npc(oscControl)->sync = false;
    if(lpfEnabled) {
        sample = s1 * lpfOsc1Level + s2 * lpfOsc2Level + s3 * lpfOsc3Level;
        auto f = pitch + modulation(0, 4, lpfCutoffModDepths) + flpstatic;
        sample = npc(lpFilter)->filter(sample, ctoot::synth::SynthChannel::midiFreq(f) * ValorSynthChannel_this->inverseNyquist);
    }
    if(svfEnabled) {
        auto sample2 = s1 * svfOsc1Level + s2 * svfOsc2Level + s3 * svfOsc3Level;
        auto f = pitch + modulation(0, 4, svfCutoffModDepths) + fsvstatic;
        sample += npc(svFilter)->filter(sample2, ctoot::synth::SynthChannel::midiFreq(f) * ValorSynthChannel_this->inverseNyquist);
    }
    return sample * ampLevel * npc(envelopeA)->getEnvelope(release_);
}

float ctoot::synth::channels::valor::ValorSynthChannel_Example2Voice::modulation(int32_t start, int32_t len, ::floatArray* depths)
{
    auto sample = 0.0f;
    for (auto i = start; i < start + len; i++) {
        sample += (*modSamples)[i] * (*depths)[i];
    }
    return sample;
}

bool ctoot::synth::channels::valor::ValorSynthChannel_Example2Voice::isComplete()
{
    return npc(envelopeA)->isComplete();
}

extern java::lang::Class *class_(const char16_t *c, int n);

java::lang::Class* ctoot::synth::channels::valor::ValorSynthChannel_Example2Voice::class_()
{
    static ::java::lang::Class* c = ::class_("uk.org.toot.synth.channels.valor.ValorSynthChannel.Example2Voice", 64);
    return c;
}

java::lang::Class* ctoot::synth::channels::valor::ValorSynthChannel_Example2Voice::getClass0()
{
    return class_();
}

