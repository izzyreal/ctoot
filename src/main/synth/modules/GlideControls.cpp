#include <synth/modules/GlideControls.hpp>

#include <control/BooleanControl.hpp>
#include <control/Control.hpp>
#include <control/FloatControl.hpp>
#include <control/LogLaw.hpp>

using namespace ctoot::synth::modules;
using namespace std;

weak_ptr<ctoot::control::ControlLaw> GlideControls::TIME_LAW()
{
	static auto res = make_shared<ctoot::control::LogLaw>(10.0f, 1000.0f, "ms");
	return res;
}

GlideControls::GlideControls(int32_t idOffset)
	: GlideControls(112, "Glide", idOffset)
{
}

GlideControls::GlideControls(int32_t id, std::string name, int32_t idOffset)
	: ctoot::control::CompoundControl(id, name)
{
    this->idOffset = idOffset;
    createControls();
    deriveSampleRateIndependentVariables();
}

void GlideControls::derive(ctoot::control::Control* c)
{
	switch (c->getId() - idOffset) {
	case ENABLE:
		glideEnable = deriveEnable();
		break;
	case TIME:
		glideMillis = deriveTime();
		break;
	}
}

void GlideControls::createControls()
{
	auto ec = createEnableControl();
	enableControl = ec;
    add(std::move(ec));
	
	auto tc = createTimeControl();
	timeControl = tc;
    add(std::move(tc));
}

void GlideControls::deriveSampleRateIndependentVariables()
{
    glideEnable = deriveEnable();
    glideMillis = deriveTime();
}

bool GlideControls::deriveEnable()
{
    return enableControl.lock()->getValue();
}

int32_t GlideControls::deriveTime()
{
    return timeControl.lock()->getValue();
}

shared_ptr<ctoot::control::BooleanControl> GlideControls::createEnableControl()
{
    auto control = make_shared<ctoot::control::BooleanControl>(ENABLE + idOffset, "On", true);
    return control;
}

shared_ptr<ctoot::control::FloatControl> GlideControls::createTimeControl()
{
    return make_shared<ctoot::control::FloatControl>(TIME + idOffset, "Time", TIME_LAW(), 1.0f, 100.0f);
}

int32_t ctoot::synth::modules::GlideControls::getGlideMilliseconds()
{
    return glideMillis;
}

bool ctoot::synth::modules::GlideControls::isGlideEnabled()
{
    return glideEnable;
}
