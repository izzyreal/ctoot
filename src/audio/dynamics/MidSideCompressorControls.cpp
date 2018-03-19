#include <audio/dynamics/MidSideCompressorControls.hpp>

#include <audio/dynamics/CompressorControls.hpp>
#include <audio/dynamics/DynamicsControlIds.hpp>
#include <audio/dynamics/DynamicsIds.hpp>
#include <audio/dynamics/MidSideCompressorControls1.hpp>
#include <control/Control.hpp>

using namespace ctoot::audio::dynamics;
using namespace std;

void MidSideCompressorControls::init()
{
    threshold = vector<float>(2);
    inverseThreshold = vector<float>(2);
    knee = vector<float>(2);
    inverseRatio = vector<float>(2);
    attack = vector<float>(2);
    hold = vector<int32_t>(2);
    release = vector<float>(2);
    gain = vector<float>(2);
    depth = vector<float>(2);
}

MidSideCompressorControls::MidSideCompressorControls()
	: ctoot::audio::core::AudioControls(DynamicsIds::MID_SIDE_COMPRESSOR_ID, "Mid-Side Compressor")
{
    init();
	auto m = make_shared<MidSideCompressorControls1>("Mid", 0);
	mid = m;
	add(std::move(m));
	auto s = make_shared<MidSideCompressorControls1>("Side", 16);
	side = s;
	add(std::move(s));
    deriveIndependentVariables();
    deriveDependentVariables();
}

void MidSideCompressorControls::deriveIndependentVariables()
{
    threshold[0] = mid.lock()->getThreshold();
    threshold[1] = side.lock()->getThreshold();
    inverseThreshold[0] = mid.lock()->getInverseThreshold();
    inverseThreshold[1] = side.lock()->getInverseThreshold();
    inverseRatio[0] = mid.lock()->getInverseRatio();
    inverseRatio[1] = side.lock()->getInverseRatio();
    gain[0] = mid.lock()->getGain();
    gain[1] = side.lock()->getGain();
    depth[0] = mid.lock()->getDepth();
    depth[1] = side.lock()->getDepth();
}

void MidSideCompressorControls::deriveDependentVariables()
{
    attack[0] = mid.lock()->getAttack();
    attack[1] = side.lock()->getAttack();
    release[0] = mid.lock()->getRelease();
    release[1] = side.lock()->getRelease();
}

void MidSideCompressorControls::derive(ctoot::control::Control* c)
{
	auto id = c->getId();
	auto n = 0;
	auto cc = mid;
	if (id >= 16) {
		n = 1;
		cc = side;
		id -= 16;
	}
	switch (id) {
	case DynamicsControlIds::THRESHOLD:
		threshold[n] = cc.lock()->getThreshold();
		inverseThreshold[n] = cc.lock()->getInverseThreshold();
	case DynamicsControlIds::RATIO:
		inverseRatio[n] = cc.lock()->getInverseRatio();
		break;
	case DynamicsControlIds::ATTACK:
		attack[n] = cc.lock()->getAttack();
		break;
	case DynamicsControlIds::HOLD:
		hold[n] = cc.lock()->getHold();
		break;
	case DynamicsControlIds::RELEASE:
		release[n] = cc.lock()->getRelease();
		break;
	case DynamicsControlIds::GAIN:
		gain[n] = cc.lock()->getGain();
		break;
	case DynamicsControlIds::DEPTH:
		depth[n] = cc.lock()->getDepth();
		break;
	}
}

void MidSideCompressorControls::update(float sampleRate)
{
    mid.lock()->update(sampleRate);
    side.lock()->update(sampleRate);
    deriveDependentVariables();
}

vector<float> MidSideCompressorControls::getThreshold()
{
    return threshold;
}

vector<float> MidSideCompressorControls::getInverseThreshold()
{
    return inverseThreshold;
}

vector<float> MidSideCompressorControls::getKnee()
{
    return knee;
}

vector<float> MidSideCompressorControls::getInverseRatio()
{
    return inverseRatio;
}

vector<float> MidSideCompressorControls::getAttack()
{
    return attack;
}

vector<int32_t> MidSideCompressorControls::getHold()
{
    return hold;
}

vector<float> MidSideCompressorControls::getRelease()
{
    return release;
}

vector<float> MidSideCompressorControls::getGain()
{
    return gain;
}

vector<float> MidSideCompressorControls::getDepth()
{
    return depth;
}

void MidSideCompressorControls::setDynamicGain(float gainM, float gainS)
{
    mid.lock()->setDynamicGain(gainM);
    side.lock()->setDynamicGain(gainS);
}

bool MidSideCompressorControls::isBypassed()
{
    return AudioControls::isBypassed();
}
