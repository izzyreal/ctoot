#include <synth/modules/oscillator/MultiWaveOscillator.hpp>

#include <synth/SynthChannel.hpp>
#include <synth/modules/oscillator/MultiWave.hpp>
#include <synth/modules/oscillator/MultiWaveOscillatorVariables.hpp>
#include <synth/modules/oscillator/OscillatorControl.hpp>
#include <synth/modules/oscillator/Wave.hpp>

#include <Logger.hpp>

using namespace ctoot::synth::modules::oscillator;

MultiWaveOscillator::MultiWaveOscillator(ctoot::synth::SynthChannel* channel, MultiWaveOscillatorVariables* oscillatorVariables, float frequency)
{
	this->channel = channel;
	vars = oscillatorVariables;
	master = vars->isMaster();
	multiWave = vars->getMultiWave();
	auto octave = vars->getOctave();
	switch (octave) {
	case -2:
		frequency /= 4;
		break;
	case -1:
		frequency /= 2;
		break;
	case +1:
		frequency *= 2;
		break;
	case +2:
		frequency *= 4;
		break;
	}

	this->frequency = frequency;
	waveIndex = multiWave.lock()->getIndex(frequency);
	wave = multiWave.lock()->getWave(waveIndex);
	waveSize = wave.lock()->getData()->size() - 1;
	k = wave.lock()->getPeriod() * frequency;
	index = waveSize * multiWave.lock()->getWidthStartFactor(vars->getWidth());
}

void MultiWaveOscillator::setSampleRate(int32_t sampleRate)
{
    increment = k / sampleRate;
    k2 = frequency / increment;
}

void MultiWaveOscillator::update()
{
	currentIncrement = increment * channel->getBendFactor() * vars->getDetuneFactor();
	sync = !master;
	width = vars->getWidth();
	scalar = multiWave.lock()->getWidthScalar(width);
	offset = multiWave.lock()->getWidthOffset(width);
}

float MultiWaveOscillator::getSample(float mod, float wmod, OscillatorControl* control)
{
	auto inc = currentIncrement * mod;
	if (sync) {
		if (control->sync)
			index = 0;
	}
	auto sample = wave.lock()->get(index);
	auto w = width + wmod;
	if (w > 0.99f)
		w = 0.99f;
	else if (w < 0.01f)
		w = 0.01f;

	auto ixShift = index + waveSize * w;
	if (ixShift >= waveSize)
		ixShift -= waveSize;

	sample -= wave.lock()->get(ixShift);
	index += inc;
	if (index >= waveSize) {
		index -= waveSize;
		auto wi = multiWave.lock()->getIndex(k2 * inc);
		if (wi != waveIndex) {
			wave = multiWave.lock()->getWave(wi);
			waveIndex = wi;
		}
		if (master)
			control->sync = true;
	}
	return sample * scalar + offset;
}
