#include <dsp/filter/BiQuadDesigner.hpp>

#include <audio/filter/FilterTools.hpp>
#include <dsp/filter/FilterShape.hpp>
#include <dsp/filter/OrfanidisBiQuadDesigner.hpp>

#define _USE_MATH_DEFINES
#include <math.h>

using namespace ctoot::dsp::filter;
using namespace std;

bool& BiQuadDesigner::decramped()
{
    return decramped_;
}
bool BiQuadDesigner::decramped_ = true;

vector<double> BiQuadDesigner::design(FilterShape type, float dbGain, float freq, float srate, float resonance)
{
	double A, omega, sn, cs, alpha, beta;
	double a0, a1, a2, b0, b1, b2;
	if (decramped_) {
		A = pow(10, dbGain / int32_t(20));
		auto bwHz = ctoot::audio::filter::FilterTools::getHzBandwidth(freq, resonance);
		{
			auto v = type;
			if (v == FilterShape::PEQ) {
				if (abs(dbGain) > 0.1) {
					return OrfanidisBiQuadDesigner::designPeak(srate, freq, bwHz, static_cast<float>(A));
				}
				goto end_switch0;
			}
			if (v == FilterShape::NOTCH) {
				return OrfanidisBiQuadDesigner::designNotch(srate, freq, bwHz);
			}
			if (v == FilterShape::RESONATOR) {
				return OrfanidisBiQuadDesigner::designResonator(srate, freq, bwHz);
			}
			if ((v != FilterShape::PEQ) && (v != FilterShape::NOTCH) && (v != FilterShape::RESONATOR)) {
				goto end_switch0;
			}
		end_switch0:;
		}

	}
	A = pow(10, dbGain / int32_t(40));
	auto bandwidth = ctoot::audio::filter::FilterTools::getOctaveBandwidth(resonance);
	omega = int32_t(2) * M_PI * freq / srate;
	sn = sin(omega);
	cs = cos(omega);
	alpha = sn * sinh(M_LN2 / 2 * bandwidth * omega / sn);
	beta = sqrt(A + A);
	{
		auto v = type;
		if (v == FilterShape::LPF) {
			b0 = (int32_t(1) - cs) / int32_t(2);
			b1 = int32_t(1) - cs;
			b2 = (int32_t(1) - cs) / int32_t(2);
			a0 = int32_t(1) + alpha;
			a1 = -int32_t(2) * cs;
			a2 = int32_t(1) - alpha;
			goto end_switch1;
		}
		if (v == FilterShape::HPF) {
			b0 = (int32_t(1) + cs) / int32_t(2);
			b1 = -(int32_t(1) + cs);
			b2 = (int32_t(1) + cs) / int32_t(2);
			a0 = int32_t(1) + alpha;
			a1 = -int32_t(2) * cs;
			a2 = int32_t(1) - alpha;
			goto end_switch1;
		}
		if (v == FilterShape::BPF) {
			b0 = alpha;
			b1 = 0;
			b2 = -alpha;
			a0 = int32_t(1) + alpha;
			a1 = -int32_t(2) * cs;
			a2 = int32_t(1) - alpha;
			goto end_switch1;
		}
		if (v == FilterShape::NOTCH) {
			b0 = 1;
			b1 = -int32_t(2) * cs;
			b2 = 1;
			a0 = int32_t(1) + alpha;
			a1 = -int32_t(2) * cs;
			a2 = int32_t(1) - alpha;
			goto end_switch1;
		}
		if (v == FilterShape::PEQ) {
			b0 = int32_t(1) + (alpha * A);
			b1 = -int32_t(2) * cs;
			b2 = int32_t(1) - (alpha * A);
			a0 = int32_t(1) + (alpha / A);
			a1 = -int32_t(2) * cs;
			a2 = int32_t(1) - (alpha / A);
			goto end_switch1;
		}
		if (v == FilterShape::LSH) {
			b0 = A * ((A + int32_t(1)) - (A - int32_t(1)) * cs + beta * sn);
			b1 = int32_t(2) * A * ((A - int32_t(1)) - (A + int32_t(1)) * cs);
			b2 = A * ((A + int32_t(1)) - (A - int32_t(1)) * cs - beta * sn);
			a0 = (A + int32_t(1)) + (A - int32_t(1)) * cs + beta * sn;
			a1 = -int32_t(2) * ((A - int32_t(1)) + (A + int32_t(1)) * cs);
			a2 = (A + int32_t(1)) + (A - int32_t(1)) * cs - beta * sn;
			goto end_switch1;
		}
		if (v == FilterShape::HSH) {
			b0 = A * ((A + int32_t(1)) + (A - int32_t(1)) * cs + beta * sn);
			b1 = -int32_t(2) * A * ((A - int32_t(1)) + (A + int32_t(1)) * cs);
			b2 = A * ((A + int32_t(1)) + (A - int32_t(1)) * cs - beta * sn);
			a0 = (A + int32_t(1)) - (A - int32_t(1)) * cs + beta * sn;
			a1 = int32_t(2) * ((A - int32_t(1)) - (A + int32_t(1)) * cs);
			a2 = (A + int32_t(1)) - (A - int32_t(1)) * cs - beta * sn;
			goto end_switch1;
		}
		if ((((v != FilterShape::LPF) && (v != FilterShape::HPF) && (v != FilterShape::BPF) && (v != FilterShape::NOTCH) && (v != FilterShape::PEQ) && (v != FilterShape::LSH) && (v != FilterShape::HSH)))) {
			return {};
		}
	end_switch1:;
	}

	auto a = vector<double>(5);
	a[int32_t(0)] = b0 / a0;
	a[int32_t(1)] = b1 / a0;
	a[int32_t(2)] = b2 / a0;
	a[int32_t(3)] = a1 / a0;
	a[int32_t(4)] = a2 / a0;
	return a;
}
