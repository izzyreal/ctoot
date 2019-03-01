#include <synth/modules/oscillator/MultiWaveOscillatorControls.hpp>

#include <control/ControlColumn.hpp>
#include <control/Control.hpp>
#include <control/EnumControl.hpp>
#include <control/FloatControl.hpp>
#include <control/LinearLaw.hpp>
#include <synth/modules/oscillator/MultiWave.hpp>
#include <synth/modules/oscillator/MultiWaveOscillatorControlColumn.hpp>
#include <synth/modules/oscillator/MultiWaveOscillatorDetuneControl.hpp>
#include <synth/modules/oscillator/MultiWaveOscillatorWaveControl.hpp>
#include <synth/modules/oscillator/MultiWaveOscillatorWidthControl.hpp>
#include <synth/modules/oscillator/MultiWaveOscillatorOctaveControl.hpp>
#include <synth/modules/oscillator/MultiWaves.hpp>
#include <synth/modules/oscillator/OscillatorIds.hpp>

using namespace ctoot::synth::modules::oscillator;
using namespace std;

vector<string> MultiWaveOscillatorControls::octaveArray = { "2", "1", "0", "-1", "-2" };

weak_ptr<ctoot::control::ControlLaw> MultiWaveOscillatorControls::TUNING_LAW()
{
	static auto res = make_shared<ctoot::control::LinearLaw>(-1.0f, 1.0f, "");
	return res;
}

weak_ptr<ctoot::control::ControlLaw> MultiWaveOscillatorControls::WIDTH_LAW()
{
	static auto res = make_shared<ctoot::control::LinearLaw>(0.01f, 0.99f, "");
	return res;
}

MultiWaveOscillatorControls::MultiWaveOscillatorControls(int32_t instanceIndex, string name, int32_t idOffset, bool master)
	:MultiWaveOscillatorControls(OscillatorIds::MULTI_WAVE_OSCILLATOR_ID, instanceIndex, name, idOffset, master)
{
}

MultiWaveOscillatorControls::MultiWaveOscillatorControls(int32_t id, int32_t instanceIndex, string name, int32_t idOffset, bool master)
	: ctoot::control::CompoundControl(id, instanceIndex, name)
{
    this->idOffset = idOffset;
    this->master = master;
    createControls();
    deriveSampleRateIndependentVariables();
    deriveSampleRateDependentVariables();
}

void MultiWaveOscillatorControls::derive(ctoot::control::Control* c)
{
	switch (c->getId() - idOffset) {
	case WAVE:
		multiWave = deriveMultiWave();
		break;
	case DETUNE:
		detuneFactor = deriveDetuneFactor();
		break;
	case WIDTH:
		width = deriveWidth();
		break;
	case OCTAVE:
		octave = deriveOctave();
		break;
	}
}

void MultiWaveOscillatorControls::createControls()
{
	if (getInstanceIndex() > 0) {
		auto dc = createDetuneControl();
		detuneControl = dc;
		derive(dc.get());
		add(std::move(dc));
	}
	auto cc = make_shared<MultiWaveOscillatorControlColumn>();

	auto wac = createWaveControl();
	waveControl = wac;
	derive(wac.get());
	cc->add(std::move(wac));

	auto oc = createOctaveControl();
	octaveControl = oc;
	derive(oc.get());
	cc->add(std::move(oc));
	add(std::move(cc));

	auto wic = createWidthControl();
	widthControl = wic;
	derive(wic.get());
	add(std::move(wic));
}

shared_ptr<ctoot::control::FloatControl> MultiWaveOscillatorControls::createDetuneControl()
{
    auto control = make_shared<MultiWaveOscillatorDetuneControl>(DETUNE + idOffset, "Detune", TUNING_LAW(), 0.0001f, 1.0f);
    return control;
}

shared_ptr<ctoot::control::EnumControl> MultiWaveOscillatorControls::createWaveControl()
{
	return make_shared<MultiWaveOscillatorWaveControl>(WAVE + idOffset, "Wave", string("Square"));
}

shared_ptr<ctoot::control::FloatControl> MultiWaveOscillatorControls::createWidthControl()
{
    auto control = make_shared<MultiWaveOscillatorWidthControl>(WIDTH + idOffset, "Width", WIDTH_LAW(), 0.01f, 0.5f);
    return control;
}

shared_ptr<ctoot::control::EnumControl> MultiWaveOscillatorControls::createOctaveControl()
{
    return make_shared<MultiWaveOscillatorOctaveControl>(OCTAVE + idOffset, "Octave", string("0"));
}

void MultiWaveOscillatorControls::deriveSampleRateIndependentVariables()
{
    detuneFactor = deriveDetuneFactor();
    multiWave = deriveMultiWave();
    width = deriveWidth();
    octave = deriveOctave();
}

void MultiWaveOscillatorControls::deriveSampleRateDependentVariables()
{
}

weak_ptr<MultiWave> MultiWaveOscillatorControls::deriveMultiWave()
{
	MLOG("deriveMultiWave");
	auto name = std::any_cast<string>(waveControl.lock()->getValue());
	return MultiWaves::get(name);
}

float MultiWaveOscillatorControls::deriveWidth()
{
    if (!widthControl.lock())
        return 0.5f;

    return widthControl.lock()->getValue();
}

float MultiWaveOscillatorControls::deriveDetuneFactor()
{
	if (!detuneControl.lock())
		return 1.0f;

	return 1.0f - detuneControl.lock()->getValue() / int32_t(100);
}

int32_t MultiWaveOscillatorControls::deriveOctave()
{
	return stoi(std::any_cast<string>(octaveControl.lock()->getValue()));
}

weak_ptr<MultiWave> MultiWaveOscillatorControls::getMultiWave()
{
	return multiWave;
}

float MultiWaveOscillatorControls::getWidth()
{
    return width;
}

float MultiWaveOscillatorControls::getSyncThreshold()
{
    return 0.0f;
}

float MultiWaveOscillatorControls::getDetuneFactor()
{
    return detuneFactor;
}

int32_t MultiWaveOscillatorControls::getOctave()
{
    return octave;
}

bool MultiWaveOscillatorControls::isMaster()
{
    return master;
}
