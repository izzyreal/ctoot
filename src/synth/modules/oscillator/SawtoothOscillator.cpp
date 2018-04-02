#include <synth/modules/oscillator/SawtoothOscillator.hpp>

#include <synth/SynthChannel.hpp>
#include <synth/modules/oscillator/MultiWave.hpp>
#include <synth/modules/oscillator/MultiWaves.hpp>
#include <synth/modules/oscillator/Wave.hpp>

using namespace ctoot::synth::modules::oscillator;
using namespace std;

SawtoothOscillator::SawtoothOscillator(ctoot::synth::SynthChannel* channel, float frequency)
{
	this->channel = channel;
	this->frequency = frequency;
	waveIndex = multiWave.lock()->getIndex(frequency);
	wave = multiWave.lock()->getWave(waveIndex);
	waveSize = wave.lock()->getData()->size() - 1;
	k = wave.lock()->getPeriod() * frequency;
}

weak_ptr<MultiWave> SawtoothOscillator::multiWave = MultiWaves::get("Square"); // yes, sawtooths are derived from squares

void SawtoothOscillator::setSampleRate(int32_t sampleRate)
{
	increment = k / sampleRate;
	k2 = frequency / increment;
}

void SawtoothOscillator::update()
{
    currentIncrement = increment * channel->getBendFactor();
}

float SawtoothOscillator::getSample(float mod)
{
	auto inc = currentIncrement * mod;
	auto sample = wave.lock()->get(index);
	index += inc;
	if (index >= waveSize) {
		index -= waveSize;
		auto wi = multiWave.lock()->getIndex(k2 * inc);
		if (wi != waveIndex) {
			wave = multiWave.lock()->getWave(wi);
			waveIndex = wi;
		}
	}
	return sample;
}
