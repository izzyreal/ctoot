#include <audio/dynamics/TremoloControls.hpp>

#include <audio/dynamics/DynamicsIds.hpp>
#include <control/ControlColumn.hpp>
#include <control/Control.hpp>
#include <control/FloatControl.hpp>
#include <control/LinearLaw.hpp>
#include <control/LogLaw.hpp>

using namespace ctoot::audio::dynamics;
using namespace std;

weak_ptr<ctoot::control::ControlLaw> TremoloControls::rateLaw()
{
	static auto res = make_shared<ctoot::control::LogLaw>(0.5f, 10.0f, "Hz");
    return res;
}

constexpr int32_t TremoloControls::RATE_ID;
constexpr int32_t TremoloControls::DEPTH_ID;

TremoloControls::TremoloControls()
	: ctoot::audio::core::AudioControls(DynamicsIds::TREMOLO_ID, "Tremolo")
{
    auto cc = make_shared<ctoot::control::ControlColumn>();
	auto rc = createRateControl();
	rateControl = rc;
    cc->add(rc);
	auto dc = createDepthControl();
	depthControl = dc;
    cc->add(dc);
    add(cc);
}

shared_ptr<ctoot::control::FloatControl> TremoloControls::createRateControl()
{
    return make_shared<ctoot::control::FloatControl>(RATE_ID, "Rate", rateLaw(), 0.01f, 3.5f);
}

shared_ptr<ctoot::control::FloatControl> TremoloControls::createDepthControl()
{
    return make_shared<ctoot::control::FloatControl>(DEPTH_ID, "Depth", ctoot::control::LinearLaw::UNITY(), 0.01f, 0.25f);
}

float TremoloControls::getDepth()
{
    return depthControl.lock()->getValue();
}

float TremoloControls::getRate()
{
    return rateControl.lock()->getValue();
}

bool TremoloControls::isBypassed()
{
    return AudioControls::isBypassed();
}
