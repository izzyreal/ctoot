#include <synth/modules/oscillator/DSFOscillatorW.hpp>

#include <dsp/Cosine.hpp>
#include <dsp/Sine.hpp>

#define _USE_MATH_DEFINES
#include <math.h>

using namespace ctoot::synth::modules::oscillator;
using namespace std;

DSFOscillatorW::DSFOscillatorW(double wn, double wp, int32_t np, float a)
{
    /* assert((wn > 0.0f && wn < M_PI) : ::java::lang::StringBuilder().append("wn=")->append(wn)->toString()) */ ;
    /* assert(np > 0 : ::java::lang::StringBuilder().append("np=")->append(np)->toString()) */ ;
    /* assert((a >= 0 && a < 1.0f) : ::java::lang::StringBuilder().append("a=")->append(a)->toString()) */ ;
    this->np = np;
    if(wn * np >= M_PI)
        np = static_cast< int32_t >((M_PI / wn));

    sine1 = make_shared<ctoot::dsp::Sine>(wn * (np + int32_t(1)));
    sine2 = make_shared<ctoot::dsp::Sine>(wn * np);
    sine3 = make_shared<ctoot::dsp::Sine>(wn);
    cosine = make_shared<ctoot::dsp::Cosine>(wn);
    update(a);
}

void DSFOscillatorW::update(float a)
{
    this->a = a;
    aN = pow(a, np);
}

float DSFOscillatorW::getSample()
{
	auto denom = (int32_t(1) - int32_t(2) * a * cosine->out() + a * a);
	if (denom == 0)
		return 0.0f;

	return static_cast<float>(((((a * sine2->out() - sine1->out()) * aN + sine3->out()) * a) / denom));
}
