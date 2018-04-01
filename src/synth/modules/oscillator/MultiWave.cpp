#include <synth/modules/oscillator/MultiWave.hpp>

#include <synth/SynthChannel.hpp>
#include <synth/modules/oscillator/SingleWave.hpp>
#include <synth/modules/oscillator/Wave.hpp>

#define _USE_MATH_DEFINES
#include <math.h>

using namespace ctoot::synth::modules::oscillator;
using namespace std;

vector<int8_t> MultiWave::index;

MultiWave::MultiWave(int32_t size, float fNyquist)
{
    if (index.size() == 0)
        createIndex();

    createWaves(size, fNyquist);
}

void MultiWave::createIndex()
{
	index = vector<int8_t>(25088);
	auto prevIx = int32_t(0);
	for (int n = 0; n < 128; n++) {
		auto f = ctoot::synth::SynthChannel::midiFreq(n);
		auto ix = static_cast<int32_t>(2 * f);
		for (int j = prevIx; j <= ix; j++) {
			index[j] = static_cast<int8_t>(n);
		}
		prevIx = ix + 1;
	}
}

void MultiWave::createWaves(int32_t size, float fNyquist)
{
	sinetable = vector<float>(size);
	for (int i = 0; i < size; i++) {
		sinetable[i] = sin(2.0 * M_PI * double(i) / size);
	}
	float max = 0.0f;
	for (int n = 0; n < 128; n++) {
		auto data = vector<float>(size + 1);
		auto f = ctoot::synth::SynthChannel::midiFreq(n);
		auto npartials = static_cast<int32_t>(fNyquist / f);
		auto sign = int32_t(1);
		float comp = int32_t(0);
		for (auto p = int32_t(0); p < npartials; p++) {
			comp = static_cast<float>(cos(p * M_PI / 2 / npartials));
			comp *= comp;
			sign = partial(&data, data.size() - 1, p + 1, sign, comp);
			data[data.size() - 1] = data[0];
		}
		if (n == 0)
			max = getMax(&data);

		normalise(&data, max);
		wave[n] = make_shared<SingleWave>(data, data.size() - 1);
	}
	sinetable.clear();
}

float MultiWave::getMax(vector<float>* data)
{
	auto max = 0.0f;
	for (auto i = int32_t(0); i < data->size(); i++) {
		auto a = abs((*data)[i]);
		if (a > max)
			max = a;
	}
	return max;
}

void MultiWave::normalise(vector<float>* data, float max)
{
	for (int i = 0; i < data->size(); i++) {
		(*data)[i] /= max;
	}
}

int32_t MultiWave::getIndex(float freq)
{
	if (freq > 12544)
		return 127;
	return index[static_cast<int32_t>(freq + freq)];
}

weak_ptr<Wave> MultiWave::getWave(int32_t n)
{
    return wave[n];
}

float MultiWave::getWidthStartFactor(float width)
{
    return 0;
}

float MultiWave::getWidthScalar(float width)
{
    return 1.0f;
}

float MultiWave::getWidthOffset(float width)
{
    return 0.0f;
}
