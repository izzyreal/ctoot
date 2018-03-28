#include <synth/modules/oscillator/SawtoothMultiWave.hpp>

using namespace ctoot::synth::modules::oscillator;

SawtoothMultiWave::SawtoothMultiWave(int32_t size, float fNyquist)
{
    super::ctor(size, fNyquist);
}

float ctoot::synth::modules::oscillator::SawtoothMultiWave::getWidthOffset(float width)
{
    return 1.0f - int32_t(2) * width;
}

int32_t ctoot::synth::modules::oscillator::SawtoothMultiWave::partial(::floatArray* data, int32_t length, int32_t partial, int32_t sign, float comp)
{
    auto amp = comp / partial;
    for (auto i = int32_t(0); i < length; i++) {
        (*data)[i] += amp * (*sinetable)[(i * partial) % length];
    }
    return sign;
}
