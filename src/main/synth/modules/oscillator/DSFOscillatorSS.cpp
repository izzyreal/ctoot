#include <synth/modules/oscillator/DSFOscillatorSS.hpp>

#include <dsp/Cosine.hpp>
#include <dsp/Sine.hpp>

#define _USE_MATH_DEFINES
#include <math.h>

using namespace ctoot::synth::modules::oscillator;
using namespace std;

DSFOscillatorSS::DSFOscillatorSS(double wn, double wp, int32_t np, float a)
{
	/* assert((wn > 0.0f && wn < M_PI) : ::java::lang::StringBuilder().append("wn=")->append(wn)->toString()) */;
	/* assert(wp > 0.0f : ::java::lang::StringBuilder().append("wp=")->append(wp)->toString()) */;
	/* assert(np > 0 : ::java::lang::StringBuilder().append("np=")->append(np)->toString()) */;
	/* assert((a >= 0 && a < 1.0f) : ::java::lang::StringBuilder().append("a=")->append(a)->toString()) */;
	if (wn + wp * np >= M_PI)
		np = static_cast<int32_t>(((M_PI - wn) / wp));

	this->np = np;
	s1 = make_shared<ctoot::dsp::Sine>(wn + wp * (np - int32_t(1)));
	s2 = make_shared<ctoot::dsp::Sine>(wn + wp * np);
	s3 = make_shared<ctoot::dsp::Sine>(wn - wp);
	s4 = make_shared<ctoot::dsp::Sine>(wn);
	cosine = make_shared<ctoot::dsp::Cosine>(wp);
	update(a);
}

void DSFOscillatorSS::update(float a)
{
    this->a = a;
    aNm1 = pow(a, np - 1);
}

float DSFOscillatorSS::getSample()
{
	auto denom = (1 - 2 * a * cosine->out() + a * a);
	if (denom == 0)
		return 0.0f;

	return static_cast<float>(((s4->out() - a * (s3->out() + aNm1 * (s2->out() - a * s1->out()))) / denom));
}
