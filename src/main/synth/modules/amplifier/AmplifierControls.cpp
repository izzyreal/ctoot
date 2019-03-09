#include <synth/modules/amplifier/AmplifierControls.hpp>

#include <audio/core/KVolumeUtils.hpp>
#include <control/Control.hpp>
#include <control/FloatControl.hpp>
#include <control/LinearLaw.hpp>
#include <synth/modules/amplifier/AmplifierControlIds.hpp>
#include <synth/modules/amplifier/AmplifierIds.hpp>

using namespace ctoot::synth::modules::amplifier;
using namespace std;

weak_ptr<ctoot::control::ControlLaw> AmplifierControls::LEVEL_LAW()
{
	static auto res = make_shared<ctoot::control::LinearLaw>(-20.0f, 20.0f, "dB");
	return res;
}

AmplifierControls::AmplifierControls(int32_t instanceIndex, std::string name, int32_t idOffset)
	: AmplifierControls(AmplifierIds::AMPLIFIER_ID, instanceIndex, name, idOffset, "V")
{
}

AmplifierControls::AmplifierControls(int32_t instanceIndex, std::string name, int32_t idOffset, std::string options)
	: AmplifierControls(AmplifierIds::AMPLIFIER_ID, instanceIndex, name, idOffset, options)
{
}

AmplifierControls::AmplifierControls(int32_t id, int32_t instanceIndex, std::string name, int32_t idOffset, std::string options)
	: ctoot::control::CompoundControl(id, instanceIndex, name)
{
    this->idOffset = idOffset;
	hasVelocity = options.find("V") != string::npos;
    createControls();
    deriveSampleRateIndependentVariables();
}

void AmplifierControls::derive(ctoot::control::Control* c)
{
    switch (c->getId() - idOffset) {
    case AmplifierControlIds::VEL_TRACK:
        velocityTrack = deriveVelocityTrack();
        break;
    case AmplifierControlIds::LEVEL:
        level = deriveLevel();
        break;
    }

}

void AmplifierControls::createControls()
{
	if (hasVelocity) {
		auto vtc = createVelocityTrackControl();
		velocityTrackControl = vtc;
		add(std::move(vtc));
	}
	auto lc = createLevelControl();
	levelControl = lc;
	add(std::move(lc));
}

void AmplifierControls::deriveSampleRateIndependentVariables()
{
    velocityTrack = deriveVelocityTrack();
    level = deriveLevel();
}

float AmplifierControls::deriveVelocityTrack()
{
    return hasVelocity ? velocityTrackControl.lock()->getValue() : static_cast< float >(int32_t(1));
}

float AmplifierControls::deriveLevel()
{
    return static_cast< float >(ctoot::audio::core::KVolumeUtils::log2lin(levelControl.lock()->getValue()));
}

shared_ptr<ctoot::control::FloatControl> AmplifierControls::createVelocityTrackControl()
{
    auto control = make_shared<ctoot::control::FloatControl>(AmplifierControlIds::VEL_TRACK + idOffset, "Velocity", ctoot::control::LinearLaw::UNITY(), 0.01f, 0.5f);
    return control;
}

shared_ptr<ctoot::control::FloatControl> AmplifierControls::createLevelControl()
{
    return make_shared<ctoot::control::FloatControl>(AmplifierControlIds::LEVEL + idOffset, "Level", LEVEL_LAW(), 0.01f, 0.0f);
}

float AmplifierControls::getVelocityTrack()
{
	return velocityTrack;
}

float AmplifierControls::getLevel()
{
    return level;
}
