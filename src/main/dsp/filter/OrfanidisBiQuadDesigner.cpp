#include <dsp/filter/OrfanidisBiQuadDesigner.hpp>

#define _USE_MATH_DEFINES
#include <math.h>  

using namespace ctoot::dsp::filter;
using namespace std;

float OrfanidisBiQuadDesigner::THREE_DB_ = static_cast< float >((sqrt(2) / int32_t(2)));

constexpr double OrfanidisBiQuadDesigner::PI2;

vector<double> OrfanidisBiQuadDesigner::designPeak(float fs, float f0, float fb, float G)
{
    return design(fs, f0, fb, 1.0f, G, static_cast< float >(sqrt(G)));
}

vector<double> OrfanidisBiQuadDesigner::designResonator(float fs, float f0, float fb)
{
    return design(fs, f0, fb, 0.0f, 1.0f, THREE_DB_);
}

vector<double> OrfanidisBiQuadDesigner::designNotch(float fs, float f0, float fb)
{
    return design(fs, f0, fb, 1.0f, 0.0f, THREE_DB_);
}

vector<double> OrfanidisBiQuadDesigner::design(float fs, float f0, float fb, float G0, float G, float Gb)
{
	auto w0 = 2.0f * M_PI * f0 / fs;
	auto wb = 2.0f * M_PI * fb / fs;
	auto wb2 = wb * wb;
	double G02 = G0 * G0;
	double G2 = G * G;
	double Gb2 = Gb * Gb;
	auto F = abs(G2 - Gb2);
	auto G00 = abs(G2 - G02);
	auto F00 = abs(Gb2 - G02);
	auto L = w0 * w0 - PI2;
	auto L2 = L * L;
	auto R = PI2 * wb2 * F00 / F;
	auto num = G02 * L2 + G2 * R;
	auto den = L2 + R;
	auto G1 = sqrt(num / den);
	auto G01 = abs(G2 - G0 * G1);
	auto G11 = abs(G2 - G1 * G1);
	auto F01 = abs(Gb2 - G0 * G1);
	auto F11 = abs(Gb2 - G1 * G1);
	auto r0 = tan(w0 / int32_t(2));
	auto W2 = sqrt(G11 / G00) * r0 * r0;
	auto rb = (int32_t(1) + sqrt(F00 / F11) * W2) * tan(wb / int32_t(2));
	auto C = F11 * rb * rb - int32_t(2) * W2 * (F01 - sqrt(F00 * F11));
	auto D = int32_t(2) * W2 * (G01 - sqrt(G00 * G11));
	auto A = sqrt((C + D) / F);
	auto B = sqrt((G2 * C + Gb2 * D) / F);
	auto a0 = int32_t(1) + W2 + A;
	auto a1 = -int32_t(2) * (int32_t(1) - W2);
	auto a2 = int32_t(1) + W2 - A;
	auto b0 = G1 + G0 * W2 + B;
	auto b1 = -int32_t(2) * (G1 - G0 * W2);
	auto b2 = G1 + G0 * W2 - B;
	auto a = vector<double>(5);
	a[int32_t(0)] = b0 / a0;
	a[int32_t(1)] = b1 / a0;
	a[int32_t(2)] = b2 / a0;
	a[int32_t(3)] = a1 / a0;
	a[int32_t(4)] = a2 / a0;
	return a;
}
