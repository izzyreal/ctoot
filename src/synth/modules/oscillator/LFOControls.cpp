#include <synth/modules/oscillator/LFOControls.hpp>

#include <control/Control.hpp>
#include <control/EnumControl.hpp>
#include <control/FloatControl.hpp>
#include <control/LinearLaw.hpp>
#include <control/LogLaw.hpp>
#include <synth/modules/oscillator/LFOConfig.hpp>
#include <synth/modules/oscillator/ShapeControl.hpp>
#include <synth/modules/oscillator/OscillatorIds.hpp>

using namespace ctoot::synth::modules::oscillator;
using namespace std;

LFOControls::LFOControls(int32_t instanceIndex, std::string name, int32_t idOffset, LFOConfig* cfg)
	: LFOControls(OscillatorIds::LFO_ID, instanceIndex, name, idOffset, cfg)
{
}

LFOControls::LFOControls(int32_t id, int32_t instanceIndex, std::string name, int32_t idOffset, LFOConfig* cfg)
	: ctoot::control::CompoundControl(id, instanceIndex, name)
{
    this->idOffset = idOffset;
    config = cfg;
    createControls();
    deriveSampleRateIndependentVariables();
    deriveSampleRateDependentVariables();
}

void LFOControls::derive(ctoot::control::Control* c)
{
	switch (c->getId() - idOffset) {
	case FREQUENCY:
		frequency = deriveFrequency();
		break;
	case DEVIATION:
		deviation = deriveDeviation();
		break;
	case SHAPE:
		sine = deriveShape();
		break;
	}
}

void LFOControls::createControls()
{
	auto sc = createShapeControl();
	shapeControl = sc;
	derive(sc.get());
	add(std::move(sc));

	auto fc = createFrequencyControl();
	frequencyControl = fc;
	derive(fc.get());
	add(std::move(fc));

	if (config->deviation > 0) {
		auto dc = createDeviationControl();
		deviationControl = dc;
		derive(dc.get());
		add(std::move(dc));
	}
}

shared_ptr<ctoot::control::EnumControl> LFOControls::createShapeControl()
{
	return make_shared<ShapeControl>(SHAPE + idOffset, "Shape", "Sine");
}

shared_ptr<ctoot::control::FloatControl> LFOControls::createFrequencyControl()
{
    auto law = make_shared<ctoot::control::LogLaw>(config->rateMin, config->rateMax, "Hz");
    auto control = make_shared<ctoot::control::FloatControl>(FREQUENCY + idOffset, "Frequency", law, 0.1f, config->rate);
	laws.push_back(std::move(law));
    return control;
}

shared_ptr<ctoot::control::FloatControl> LFOControls::createDeviationControl()
{
    auto law = make_shared<ctoot::control::LinearLaw>(0.0f, config->deviationMax, "Hz");
    auto control = make_shared<ctoot::control::FloatControl>(FREQUENCY + idOffset, "Deviation", law, 0.1f, config->deviation);
	laws.push_back(std::move(law));
    return control;
}

void LFOControls::deriveSampleRateIndependentVariables()
{
	frequency = deriveFrequency();
	deviation = deriveDeviation();
	sine = deriveShape();
}

void LFOControls::deriveSampleRateDependentVariables()
{
}

float LFOControls::deriveFrequency()
{
    return frequencyControl.lock()->getValue();
}

float LFOControls::deriveDeviation()
{
	if (!deviationControl.lock())
		return 0.0f;

	return deviationControl.lock()->getValue();
}

bool ctoot::synth::modules::oscillator::LFOControls::deriveShape()
{
	return boost::any_cast<string>(shapeControl.lock()->getValue()).compare("Sine") == 0;
}

float ctoot::synth::modules::oscillator::LFOControls::getFrequency()
{
    return frequency;
}

float ctoot::synth::modules::oscillator::LFOControls::getDeviation()
{
    return deviation;
}

bool ctoot::synth::modules::oscillator::LFOControls::isSine()
{
    return sine;
}
