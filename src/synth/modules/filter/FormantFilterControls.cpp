#include <synth/modules/filter/FormantFilterControls.hpp>

#include <control/BooleanControl.hpp>
#include <control/ControlColumn.hpp>
#include <control/Control.hpp>
#include <control/FloatControl.hpp>
#include <control/LawControl.hpp>
#include <control/LinearLaw.hpp>
#include <control/LogLaw.hpp>
#include <synth/modules/filter/FilterIds.hpp>

#include <cmath>

using namespace ctoot::synth::modules::filter;
using namespace std;

weak_ptr<ctoot::control::ControlLaw> FormantFilterControls::FREQ_LAW()
{
	static auto res = make_shared<ctoot::control::LogLaw>(100, 5000, "Hz");
	return res;
}

weak_ptr<ctoot::control::ControlLaw> FormantFilterControls::SHIFT_LAW()
{
	
	static auto res = make_shared<ctoot::control::LogLaw>(0.25f, 4.0f, "");
	return res;
}

FormantFilterControls::FormantFilterControls(int32_t instanceIndex, std::string name, int32_t idOffset)
	: ctoot::control::CompoundControl(FilterIds::FORMANT_FILTER_ID, instanceIndex, name)
{
	this->idOffset = idOffset;
	frequencyControl = vector<weak_ptr<ctoot::control::FloatControl>>(nBands);
	levelControl = vector<weak_ptr<ctoot::control::FloatControl>>(nBands);
	frequency = vector<float>(nBands);
	level = vector<float>(nBands);
	createControls();
	deriveSampleRateIndependentVariables();
	deriveSampleRateDependentVariables();
}

void FormantFilterControls::derive(ctoot::control::Control* c)
{
	auto id = c->getId() - idOffset;
	int32_t n;
	switch (id) {
	case RESONANCE:
		resonance = deriveResonance();
		break;
	case FREQSHIFT:
		frequencyShift = deriveFrequencyShift();
		break;
	case ENABLE:
		bypass = !deriveEnable();
		break;
	default:
		n = (id / 2) - 1;
		if ((id & 1) == 0) {
			frequency[n] = deriveFrequency(n);
		}
		else {
			level[n] = deriveLevel(n);
		}
	}
}

void FormantFilterControls::createControls()
{
	for (int i = 0; i < nBands; i++) {
		auto col = make_shared<ctoot::control::ControlColumn>();
		auto fc = createFrequencyControl(i);
		frequencyControl[i] = fc;
		col->add(std::move(fc));

		auto lc = createLevelControl(i);
		levelControl[i] = lc;
		col->add(std::move(lc));
		add(std::move(col));
	}

	auto col = make_shared<ctoot::control::ControlColumn>();

	auto pc = createPowerControl();
	enableControl = pc;
	col->add(std::move(pc));

	auto fsc = createFrequencyShiftControl();
	frequencyShiftControl = fsc;
	col->add(std::move(fsc));

	auto rc = createResonanceControl();
	resonanceControl = rc;
	col->add(std::move(rc));

	add(std::move(col));
}

void FormantFilterControls::deriveSampleRateIndependentVariables()
{
	resonance = deriveResonance();
	frequencyShift = deriveFrequencyShift();
	bypass = !deriveEnable();
	for (auto i = int32_t(0); i < nBands; i++) {
		level[i] = deriveLevel(i);
	}
}

void FormantFilterControls::deriveSampleRateDependentVariables()
{
	for (int i = 0; i < nBands; i++) {
		frequency[i] = deriveFrequency(i);
	}
}

float FormantFilterControls::deriveFrequency(int32_t n)
{
	return 2 * frequencyControl[n].lock()->getValue() / sampleRate;
}

float FormantFilterControls::deriveLevel(int32_t n)
{
    return levelControl[n].lock()->getValue();
}

float FormantFilterControls::deriveResonance()
{
    return resonanceControl.lock()->getValue();
}

float FormantFilterControls::deriveFrequencyShift()
{
    return frequencyShiftControl.lock()->getValue();
}

bool FormantFilterControls::deriveEnable()
{
    return enableControl.lock()->getValue();
}

shared_ptr<ctoot::control::FloatControl> FormantFilterControls::createFrequencyControl(int32_t n)
{
	return make_shared<ctoot::control::FloatControl>(n + n + FREQUENCY + idOffset, "Frequency", FREQ_LAW(), 1.0f, 250 * pow(2, n));
}

shared_ptr<ctoot::control::FloatControl> FormantFilterControls::createLevelControl(int32_t n)
{
    return make_shared<ctoot::control::FloatControl>(n + n + LEVEL+ idOffset, "Level", ctoot::control::LinearLaw::UNITY(), 0.01f, 1.0f);
}

shared_ptr<ctoot::control::FloatControl> FormantFilterControls::createResonanceControl()
{
    return make_shared<ctoot::control::FloatControl>(RESONANCE + idOffset, "Resonance", ctoot::control::LinearLaw::UNITY(), 0.01f, 0.25f);
}

shared_ptr<ctoot::control::FloatControl> FormantFilterControls::createFrequencyShiftControl()
{
	return make_shared<ctoot::control::FloatControl>(FREQSHIFT + idOffset, "Shift", SHIFT_LAW(), 0.1f, 1.0f);
}

shared_ptr<ctoot::control::BooleanControl> FormantFilterControls::createPowerControl()
{
    auto control = make_shared<ctoot::control::BooleanControl>(ENABLE + idOffset, "Power", false);
    control->setAnnotation("5010");
    return control;
}

void FormantFilterControls::setSampleRate(int32_t rate)
{
	if (sampleRate != rate) {
		sampleRate = rate;
		deriveSampleRateDependentVariables();
	}
}

float FormantFilterControls::getFreqencyShift()
{
	return frequencyShift;
}

float FormantFilterControls::getFrequency(int32_t n)
{
    return frequency[n];
}

float FormantFilterControls::getLevel(int32_t n)
{
	return level[n];
}

float FormantFilterControls::getResonance()
{
    return resonance;
}

bool ctoot::synth::modules::filter::FormantFilterControls::isBypassed()
{
    return bypass;
}

int32_t ctoot::synth::modules::filter::FormantFilterControls::size()
{
    return nBands;
}
