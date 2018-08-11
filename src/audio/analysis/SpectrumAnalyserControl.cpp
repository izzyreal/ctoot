#include "SpectrumAnalyserControl.hpp"

using namespace ctoot::audio::analysis;

SpectrumAnalyserControl::SpectrumAnalyserControl()
	: FloatVectorControl(1, "SpectrumAnalyser", 16)
{
}

SpectrumAnalyserControl::~SpectrumAnalyserControl()
{
}

void SpectrumAnalyserControl::setBandCount(int count) {

}
