#include <synth/modules/mixer/SynthMixerControls.hpp>

#include <control/Control.hpp>
#include <control/FloatControl.hpp>
#include <control/LinearLaw.hpp>
#include <synth/modules/mixer/MixerIds.hpp>

using namespace ctoot::synth::modules::mixer;
using namespace std;

MixerControls::MixerControls(int32_t instanceIndex, std::string name, int32_t idOffset, int32_t count)
	: MixerControls(MixerIds::SIMPLE_MIXER_ID, instanceIndex, name, idOffset, count)
{
}

MixerControls::MixerControls(int32_t id, int32_t instanceIndex, std::string name, int32_t idOffset, int32_t count)
	: ctoot::control::CompoundControl(id, instanceIndex, name)
{
	this->idOffset = idOffset;
    this->count = count;
    level = vector<float>(count);
    createControls();
    deriveSampleRateIndependentVariables();
    deriveSampleRateDependentVariables();
}

void MixerControls::derive(ctoot::control::Control* c)
{
	auto n = c->getId() - idOffset - LEVEL;
	level[n] = deriveLevel(n);
}

void MixerControls::createControls()
{
    levelControl = vector<weak_ptr<ctoot::control::FloatControl>>(count);
    for (int i = 0; i < count; i++) {
		auto lc = createLevelControl(i);
		levelControl[i] = lc;
		add(std::move(lc));
    }
}

void MixerControls::deriveSampleRateIndependentVariables()
{
    for (auto i = int32_t(0); i < count; i++) {
        level[i] = deriveLevel(i);
    }
}

float MixerControls::deriveLevel(int32_t i)
{
    return levelControl[i].lock()->getValue();
}

void MixerControls::deriveSampleRateDependentVariables()
{
}

shared_ptr<ctoot::control::FloatControl> MixerControls::createLevelControl(int32_t i)
{
	auto control = make_shared<ctoot::control::FloatControl>(i + LEVEL + idOffset, to_string(i + 1), ctoot::control::LinearLaw::UNITY(), 0.01f, i > 0 ? 0.0f : 1.0f);
	return control;
}

int32_t MixerControls::getCount()
{
    return count;
}

float MixerControls::getLevel(int32_t n)
{
    return level[n];
}
