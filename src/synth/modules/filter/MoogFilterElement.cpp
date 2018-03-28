#include <synth/modules/filter/MoogFilterElement.hpp>

using namespace ctoot::synth::modules::filter;

float MoogFilterElement::filter(float input, float fc, float res)
{
    auto f = fc * 1.16;
    auto fb = res * (1.0 - 0.15 * f * f);
    input -= out4 * fb;
    input *= 0.35013 * (f * f) * (f * f);
    out1 = input + 0.3 * in1 + (1 - f) * out1;
    in1 = input;
    out2 = out1 + 0.3 * in2 + (1 - f) * out2;
    in2 = out1;
    out3 = out2 + 0.3 * in3 + (1 - f) * out3;
    in3 = out2;
    out4 = out3 + 0.3 * in4 + (1 - f) * out4;
    in4 = out3;
    return static_cast< float >(out4);
}
