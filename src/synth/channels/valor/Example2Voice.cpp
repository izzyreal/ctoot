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
#include <synth/modules/oscillator/MultiWaveOscillator.hpp>
#include <synth/modules/oscillator/OscillatorControl.hpp>

#define _USE_MATH_DEFINES
#include <math.h>

using namespace ctoot::synth::channels::valor;
using namespace std;

Example2Voice::Example2Voice(ValorSynthChannel* vsc, int32_t pitch, int32_t velocity, int32_t sampleRate)
	: ctoot::synth::PolyphonicSynthChannelAbstractVoice(pitch, velocity)
{
	this->vsc = vsc;
	lfo1 = new ctoot::synth::modules::oscillator::LFO(vsc->lfo1Vars, static_cast<float>(-M_PI / 2));
	lfo2 = new ctoot::synth::modules::oscillator::LFO(vsc->lfo2Vars, static_cast<float>((-M_PI / 2)));
	oscillator1 = new ctoot::synth::modules::oscillator::MultiWaveOscillator(vsc, vsc->oscillator1Vars, frequency);
	oscillator2 = new ctoot::synth::modules::oscillator::MultiWaveOscillator(vsc, vsc->oscillator2Vars, frequency);
	oscillator3 = new ctoot::synth::modules::oscillator::MultiWaveOscillator(vsc, vsc->oscillator3Vars, frequency);
	envelopeA = new ctoot::synth::modules::envelope::EnvelopeGenerator(vsc->envelopeAVars);
	envelopeA->trigger();
	envelope1 = new ctoot::synth::modules::envelope::EnvelopeGenerator(vsc->envelope1Vars);
	envelope1->trigger();
	envelope2 = new ctoot::synth::modules::envelope::EnvelopeGenerator(vsc->envelope2Vars);
	envelope2->trigger();
	lfoVib = new ctoot::synth::modules::oscillator::LFO(vsc->vibratoVars);
	envelopeVib = new ctoot::synth::modules::envelope::EnvelopeGenerator(vsc->envelopeVVars);
	envelopeVib->trigger();
	lpFilter = new ctoot::synth::modules::filter::MoogFilter2(vsc->lpFilterVars);
	svFilter = new ctoot::synth::modules::filter::StateVariableFilter(vsc->svFilterVars);
	oscControl = new ctoot::synth::modules::oscillator::OscillatorControl();
	auto ampTracking = vsc->amplifierVars->getVelocityTrack();
	ampT = velocity == 0 ? 0.0f : (1 - ampTracking * (1 - amplitude));
	setSampleRate(sampleRate);
}

void Example2Voice::setSampleRate(int32_t rate)
{
    oscillator1->setSampleRate(rate);
    oscillator2->setSampleRate(rate);
    oscillator3->setSampleRate(rate);
    lfoVib->setSampleRate(rate);
    lfo1->setSampleRate(rate);
    lfo2->setSampleRate(rate);
}

bool Example2Voice::mix(ctoot::audio::core::AudioBuffer* buffer)
{
	lfoVib->update();
	lfo1->update();
	lfo2->update();
	oscillator1->update();
	lpfOsc1Level = vsc->lpFilterMixerVars->getLevel(0);
	lpfOsc2Level = vsc->lpFilterMixerVars->getLevel(1);
	lpfOsc3Level = vsc->lpFilterMixerVars->getLevel(2);
	svfOsc1Level = vsc->svFilterMixerVars->getLevel(0);
	svfOsc2Level = vsc->svFilterMixerVars->getLevel(1);
	svfOsc3Level = vsc->svFilterMixerVars->getLevel(2);
	osc2Enabled = lpfOsc2Level + svfOsc2Level > 0.01f;
	if (osc2Enabled)
		oscillator2->update();

	osc3Enabled = lpfOsc3Level + svfOsc3Level > 0.01f;
	if (osc3Enabled)
		oscillator3->update();

	osc1WidthModDepths = vsc->osc1WidthModMixer->getDepths();
	osc2WidthModDepths = vsc->osc2WidthModMixer->getDepths();
	osc3WidthModDepths = vsc->osc3WidthModMixer->getDepths();
	lpfCutoffModDepths = vsc->lpfCutoffModMixer->getDepths();
	svfCutoffModDepths = vsc->svfCutoffModMixer->getDepths();
	vibModDepths = vsc->vibModMixer->getDepths();
	modSamples[4] = amplitude;
	modSamples[5] = vsc->getChannelPressure() / 128;
	modSamples[6] = vsc->getController(ctoot::midi::misc::Controller::MODULATION) / 128;
	vibModPre = modSamples[5] * vibModDepths[1] + modSamples[6] * vibModDepths[2];
	lpfEnabled = lpfOsc1Level + lpfOsc2Level + lpfOsc3Level > 0.01f;
	if (lpfEnabled) {
		flpstatic = modulation(4, 3, lpfCutoffModDepths);
		flpstatic += lpFilter->update();
	}
	svfEnabled = svfOsc1Level + svfOsc2Level + svfOsc3Level > 0.01f;
	if (svfEnabled) {
		fsvstatic = modulation(4, 3, svfCutoffModDepths);
		fsvstatic += svFilter->update();
	}
	ampLevel = vsc->amplifierVars->getLevel() * ampT;
	return PolyphonicSynthChannelAbstractVoice::mix(buffer);
}

float Example2Voice::getSample()
{
	auto sample = 0.0f;
	auto s2 = 0.0f;
	auto s3 = 0.0f;
	modSamples[0] = (1.0f + lfo1->getSample()) / 2;
	modSamples[1] = (1.0f + lfo2->getSample()) / 2;
	modSamples[2] = envelope1->getEnvelope(release_);
	modSamples[3] = envelope2->getEnvelope(release_);
	auto vibMod = vibModPre + envelopeVib->getEnvelope(release_) * vibModDepths[0];
	vibMod *= lfoVib->getSample() / int32_t(50);
	vibMod += 1.0f;
	auto s1 = oscillator1->getSample(vibMod, modulation(0, 2, osc1WidthModDepths), oscControl);
	if (osc2Enabled) {
		s2 = oscillator2->getSample(vibMod, modulation(0, 2, osc2WidthModDepths), oscControl);
	}
	if (osc3Enabled) {
		s3 = oscillator3->getSample(vibMod, modulation(0, 2, osc3WidthModDepths), oscControl);
	}
	oscControl->sync = false;
	if (lpfEnabled) {
		sample = s1 * lpfOsc1Level + s2 * lpfOsc2Level + s3 * lpfOsc3Level;
		auto f = pitch + modulation(0, 4, lpfCutoffModDepths) + flpstatic;
		sample = lpFilter->filter(sample, ctoot::synth::SynthChannel::midiFreq(f) * vsc->inverseNyquist);
	}
	if (svfEnabled) {
		auto sample2 = s1 * svfOsc1Level + s2 * svfOsc2Level + s3 * svfOsc3Level;
		auto f = pitch + modulation(0, 4, svfCutoffModDepths) + fsvstatic;
		sample += svFilter->filter(sample2, ctoot::synth::SynthChannel::midiFreq(f) * vsc->inverseNyquist);
	}
	return sample * ampLevel * envelopeA->getEnvelope(release_);
}

float Example2Voice::modulation(int32_t start, int32_t len, vector<float> depths)
{
	auto sample = 0.0f;
	for (auto i = start; i < start + len; i++) {
		sample += modSamples[i] * depths[i];
	}
	return sample;
}

bool Example2Voice::isComplete()
{
	return envelopeA->isComplete();
}
