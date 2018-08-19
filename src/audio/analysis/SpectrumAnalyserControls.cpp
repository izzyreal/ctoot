#include "SpectrumAnalyserControls.hpp"

using namespace ctoot::audio::analysis;
using namespace std;

SpectrumAnalyserControls::SpectrumAnalyserControls()
	: audio::core::AudioControls(1, "SpectrumAnalyser")
{
}

SpectrumAnalyserControls::~SpectrumAnalyserControls()
{
}

void SpectrumAnalyserControls::setSampleRate(float sr) {
	this->sampleRate = sr;
}

float SpectrumAnalyserControls::getSampleRate() {
	return sampleRate;
}

vector<float>* SpectrumAnalyserControls::getValues() {
	return &values;
}

void SpectrumAnalyserControls::setValues(const std::vector<float>& values) {
	this->values = values;
}

void SpectrumAnalyserControls::setValue(int index, const float value) {

	if (index > values.size() - 1) return;

	values[index] = value;

}

void SpectrumAnalyserControls::setRangeMin(int min) {
	this->min = min;
}

void SpectrumAnalyserControls::setRangeMax(int max) {
	this->max = max;
}

int SpectrumAnalyserControls::getRangeMin() {
	return min;
}

int SpectrumAnalyserControls::getRangeMax() {
	return max;
}
