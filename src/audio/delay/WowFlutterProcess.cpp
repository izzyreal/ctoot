#include <audio/delay/WowFlutterProcess.hpp>

#include <audio/delay/WowFlutterProcessVariables.hpp>

#define _USE_MATH_DEFINES
#include <math.h>  

using namespace ctoot::audio::delay;
using namespace std;

WowFlutterProcess::WowFlutterProcess(WowFlutterProcessVariables* v)
	: FrequencyModulationProcess(v)
{
	vars = v;
}

void WowFlutterProcess::sampleRateChanged()
{
    super::sampleRateChanged();
    fuid -= 1;
}

void WowFlutterProcess::cacheProcessVariables()
{
	super::cacheProcessVariables();
	level = vars->getLevel();
	auto uid = vars->getFrequencyUid();
	amplitudes = vars->getAmplitudes();
	if (fuid != uid) {
		createPhasors(vars->getFrequencies());
		fuid = uid;
	}
}

float WowFlutterProcess::modulation()
{
	auto sample = 0.0f;
	for (int i = 0; i < phasors.size(); i++) {
		sample += phasors[i]->out() * amplitudes[i];
	}
	return sample * level;
}

void WowFlutterProcess::createPhasors(vector<float> frequencies)
{
	auto const n = frequencies.size();
	deletePhasors();
	phasors = vector<ctoot::dsp::Phasor*>(n);
	for (auto i = int(0); i < n; i++) {
		phasors[i] = new ctoot::dsp::Phasor(2 * M_PI * frequencies[i] / sampleRate, 0);
	}
}

void WowFlutterProcess::deletePhasors() {
	for (auto& p : phasors) {
		if (p != nullptr)
			delete p;
	}
}

WowFlutterProcess::~WowFlutterProcess() {
	deletePhasors();
}