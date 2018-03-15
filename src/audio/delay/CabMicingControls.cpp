#include <audio/delay/CabMicingControls.hpp>

#include <control/LinearLaw.hpp>
#include <control/LogLaw.hpp>
#include <audio/delay/DelayIds.hpp>
#include <control/ControlColumn.hpp>
#include <control/Control.hpp>

#include <audio/delay/CabMicingDControl.hpp>
#include <audio/delay/CabMicingNControl.hpp>
#include <audio/delay/CabMicingControlsTap.hpp>

using namespace ctoot::audio::delay;
using namespace ctoot::control;
using namespace std;

constexpr float CabMicingControls::MILLIS_PER_INCH;
constexpr float CabMicingControls::DRIVE_UNIT_SEPARATION;

weak_ptr<ControlLaw> CabMicingControls::NEAR_DISTANCE_LAW()
{
	static auto res = make_shared<LinearLaw>(1, 12, "inches");
    return res;
}

weak_ptr<ControlLaw> CabMicingControls::POWER_LAW()
{
	static auto res = make_shared<LogLaw>(0.5f, 2.0f, "");
	return res;
}

constexpr int CabMicingControls::N_ID;
constexpr int CabMicingControls::D_ID;
constexpr int CabMicingControls::NEAR_DISTANCE_ID;
constexpr int CabMicingControls::COMB_ID;

CabMicingControls::CabMicingControls()
	: AudioControls(DelayIds::CAB_MICING_ID, "Cab.Mic")
{
    auto col = make_shared<ControlColumn>();
	auto nControlS = make_shared<CabMicingNControl>();
	nControl = nControlS;
	col->add(nControlS);

	auto dControlS = make_shared<CabMicingDControl>();
	dControl = dControlS;
	col->add(dControlS);

	auto combControlS = createCombControl();
	combControl = combControlS;
	col->add(combControlS);

	auto nearControlS = createNearControl();
	nearControl = nearControlS;
	col->add(nearControlS);

	add(col);
    
	taps.push_back(n2Tap = new CabMicingControlsTap());
    taps.push_back(n3Tap = new CabMicingControlsTap());
    taps.push_back(n4Tap = new CabMicingControlsTap());
}

vector<DelayTap*> CabMicingControls::getTaps()
{
    return taps;
}

void CabMicingControls::derive(ctoot::control::Control* c)
{
    switch (c->getId()) {
    case N_ID:
        n = extract(nControl);
        break;
    case D_ID:
        d = extract(dControl);
        separation = d + DRIVE_UNIT_SEPARATION;
        break;
    case NEAR_DISTANCE_ID:
        near = nearControl.lock()->getValue();
        break;
    case COMB_ID:
        levelPower = combControl.lock()->getValue();
        break;
    default:
        return;
    }

    calculateTaps();
}

int CabMicingControls::extract(weak_ptr<ctoot::control::EnumControl> c)
{
	auto s = boost::any_cast<string>(c.lock()->getValue());
    s = s.substr(0, s.length() - 1);
    return stoi(s);
}

void CabMicingControls::calculateTaps()
{
	auto sepsqr = separation * separation;
	auto nearsqr = near * near;
	auto d1 = offset;
	auto d2 = static_cast<float>(sqrt(d1 * d1 + sepsqr));
	auto d3 = d1 + separation;
	auto d4 = static_cast<float>(sqrt(d3 * d3 + sepsqr));
	auto l1 = static_cast<float>(sqrt(d1 * d1 + nearsqr));
	auto l2 = static_cast<float>(sqrt(d2 * d2 + nearsqr));
	auto l3 = static_cast<float>(sqrt(d3 * d3 + nearsqr));
	auto l4 = static_cast<float>(sqrt(d4 * d4 + nearsqr));
	n2Tap->level = n > 3 ? level(l2 / l1) : 0.0f;
	n3Tap->level = n > 1 ? level(l3 / l1) : 0.0f;
	n4Tap->level = n > 3 ? level(l4 / l1) : 0.0f;
	l2 -= l1;
	l3 -= l1;
	l4 -= l1;
	n2Tap->millis = l2 * MILLIS_PER_INCH;
	n3Tap->millis = l3 * MILLIS_PER_INCH;
	n4Tap->millis = l4 * MILLIS_PER_INCH;
}

float CabMicingControls::level(float in)
{
    auto out = 1.0f / static_cast< float >(pow(in, levelPower));
    return out < levelMin ? levelMin : out;
}

shared_ptr<FloatControl> CabMicingControls::createNearControl()
{
    auto c = make_shared<FloatControl>(NEAR_DISTANCE_ID, "Distance", NEAR_DISTANCE_LAW(), 0.1f, near);
    return c;
}

shared_ptr<FloatControl> CabMicingControls::createCombControl()
{
    auto c = make_shared<FloatControl>(COMB_ID, "Resonance", POWER_LAW(), 0.1f, levelPower);
    return c;
}

bool CabMicingControls::isBypassed()
{
    return AudioControls::isBypassed();
}
