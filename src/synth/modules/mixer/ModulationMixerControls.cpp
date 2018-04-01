#include <synth/modules/mixer/ModulationMixerControls.hpp>

#include <control/Control.hpp>
#include <control/FloatControl.hpp>
#include <control/LawControl.hpp>
#include <control/LinearLaw.hpp>
#include <synth/modules/mixer/MixerIds.hpp>
#include <synth/modules/mixer/DepthControl.hpp>

using namespace ctoot::synth::modules::mixer;
using namespace std;

ModulationMixerControls::ModulationMixerControls(int32_t instanceIndex, std::string name, int32_t idOffset, vector<string> labels, bool bipolar)
	: ModulationMixerControls(instanceIndex, name, idOffset, labels, bipolar, 1.0f, "")
{
}

ModulationMixerControls::ModulationMixerControls(int32_t instanceIndex, std::string name, int32_t idOffset, vector<string> labels, bool bipolar, float range, std::string units)
	: ctoot::control::CompoundControl(MixerIds::MODULATION_MIXER_ID, instanceIndex, name)
{
	this->idOffset = idOffset;
	this->count = labels.size();
	law = make_shared<ctoot::control::LinearLaw>(bipolar ? -range : 0.0f, range, units);
	depth = vector<float>(count);
	createControls(labels);
	deriveSampleRateIndependentVariables();
}

void ModulationMixerControls::derive(ctoot::control::Control* c)
{
	auto n = c->getId() - idOffset - DEPTH;
	depth[n] = deriveDepth(n);
}

void ModulationMixerControls::createControls(vector<string> labels)
{
	depthControl = vector<weak_ptr<ctoot::control::FloatControl>>(count);
	for (int i = 0; i < count; i++) {
		auto dc = createDepthControl(i, labels[i]);
		depthControl[i] = dc;
		add(std::move(dc));
	}
}

void ModulationMixerControls::deriveSampleRateIndependentVariables()
{
	for (int i = 0; i < count; i++) {
		depth[i] = deriveDepth(i);
	}
}

float ModulationMixerControls::deriveDepth(int32_t i)
{
    return depthControl[i].lock()->getValue();
}

shared_ptr<ctoot::control::FloatControl> ModulationMixerControls::createDepthControl(int32_t i, std::string label)
{
    auto control = make_shared<DepthControl>(i + DEPTH + idOffset, label, law, 0.01f, 0.0f);
    return control;
}

int32_t ModulationMixerControls::getCount()
{
    return count;
}

float ModulationMixerControls::getDepth(int32_t n)
{
    return depth[n];
}

vector<float> ModulationMixerControls::getDepths()
{
    return depth;
}
