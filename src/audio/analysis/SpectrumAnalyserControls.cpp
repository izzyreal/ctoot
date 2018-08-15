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

void SpectrumAnalyserControls::setBandCount(int count) {

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
