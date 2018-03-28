#include <synth/modules/oscillator/ParabolaMultiWave.hpp>

using namespace ctoot::synth::modules::oscillator;

ParabolaMultiWave::ParabolaMultiWave(int32_t size, float fNyquist)
{
    super::ctor(size, fNyquist);
}

float ctoot::synth::modules::oscillator::ParabolaMultiWave::getWidthStartFactor(float width)
{
    return width < 0.5f ? (1.0f - (width / int32_t(2))) : ((1.0f - width) / int32_t(2));
}

float ctoot::synth::modules::oscillator::ParabolaMultiWave::getWidthScalar(float width)
{
    return 1.0f / (int32_t(8) * (width - width * width));
}

int32_t ctoot::synth::modules::oscillator::ParabolaMultiWave::partial(::floatArray* data, int32_t length, int32_t partial, int32_t sign, float comp)
{
    auto amp = comp * int32_t(4) * sign / (partial * partial);
    for (auto i = int32_t(0); i < length; i++) {
        (*data)[i] += amp * (*sinetable)[((i * partial) + (length / int32_t(4))) % length];
    }
    return -sign;
}

void modules::oscillator::ParabolaMultiWave::normalise(::floatArray* data, float max)
{
    max /= 2;
    for (auto i = int32_t(0); i < npc(data)->length; i++) {
        (*data)[i] /= max;
        (*data)[i] -= 1;
    }
}
