#include <synth/modules/oscillator/SawtoothMultiWave.hpp>

using namespace ctoot::synth::modules::oscillator;
using namespace std;

#include <Logger.hpp>

SawtoothMultiWave::SawtoothMultiWave()
	: MultiWave()
{
}

float SawtoothMultiWave::getWidthOffset(float width)
{
    return 1.0f - 2 * width;
}

int32_t SawtoothMultiWave::partial(vector<float>* data, int32_t length, int32_t partial, int32_t sign, float comp)
{
	float amp = comp / partial;
	for (int i = 0; i < length; i++) {
		(*data)[i] += amp * sinetable[(i * partial) % length];
	}
	return sign;
}
