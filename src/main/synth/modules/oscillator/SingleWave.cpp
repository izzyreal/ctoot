#include <synth/modules/oscillator/SingleWave.hpp>

using namespace ctoot::synth::modules::oscillator;
using namespace std;

SingleWave::SingleWave(vector<float> data, float period)
{
    this->data = data;
    this->period = period;
}

vector<float>* ctoot::synth::modules::oscillator::SingleWave::getData()
{
    return &data;
}

float ctoot::synth::modules::oscillator::SingleWave::getPeriod()
{
    return period;
}

float ctoot::synth::modules::oscillator::SingleWave::get(float index)
{
    auto ix = static_cast< int32_t >(index);
    auto frac = index - ix;
    return (1.0f - frac) * data[ix] + frac * data[ix + int32_t(1)];
}
