#include <synth/modules/oscillator/ParabolaMultiWave.hpp>

using namespace ctoot::synth::modules::oscillator;
using namespace std;

ParabolaMultiWave::ParabolaMultiWave()
	: MultiWave()
{
}

float ParabolaMultiWave::getWidthStartFactor(float width)
{
    return width < 0.5f ? (1.0f - (width / 2)) : ((1.0f - width) / 2);
}

float ctoot::synth::modules::oscillator::ParabolaMultiWave::getWidthScalar(float width)
{
    return 1.0f / (8 * (width - width * width));
}

int32_t ParabolaMultiWave::partial(vector<float>* data, int32_t length, int32_t partial, int32_t sign, float comp)
{
    auto amp = comp * 4 * sign / (partial * partial);
	for (int i = 0; i < length; i++) {
        (*data)[i] += amp * sinetable[((i * partial) + (length / 4)) % length];
    }
    return -sign;
}

void ParabolaMultiWave::normalise(vector<float>* data, float max)
{
	max /= 2;
	for (int i = 0; i < data->size(); i++) {
		(*data)[i] /= max;
		(*data)[i] -= 1;
	}
}
