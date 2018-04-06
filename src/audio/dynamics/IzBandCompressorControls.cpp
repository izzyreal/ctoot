#include <audio/dynamics/IzBandCompressorControls.hpp>

#include <audio/dynamics/CompressorControls.hpp>
#include <audio/dynamics/DynamicsControlIds.hpp>
#include <audio/dynamics/DynamicsIds.hpp>
#include <audio/dynamics/IzCompressorControls.hpp>
#include <control/Control.hpp>

using namespace ctoot::audio::dynamics;
using namespace std;

IzBandCompressorControls::IzBandCompressorControls(string band)
	: ctoot::audio::core::AudioControls(DynamicsIds::MID_SIDE_COMPRESSOR_ID, "IzBand Compressor")
{
	auto cc = make_shared<IzCompressorControls>(band, 0);
	compressorControls = cc;
	add(std::move(cc));
	deriveIndependentVariables();
	deriveDependentVariables();
}

IzBandCompressorControls::IzBandCompressorControls()
	: ctoot::audio::core::AudioControls(DynamicsIds::MID_SIDE_COMPRESSOR_ID, "IzBand Compressor")
{
	auto cc = make_shared<IzCompressorControls>("Band", 0);
	compressorControls = cc;
	add(std::move(cc));
    deriveIndependentVariables();
    deriveDependentVariables();
}

void IzBandCompressorControls::deriveIndependentVariables()
{
    threshold = compressorControls.lock()->getThreshold();
    inverseThreshold = compressorControls.lock()->getInverseThreshold();
    inverseRatio = compressorControls.lock()->getInverseRatio();
    gain = compressorControls.lock()->getGain();
    depth = compressorControls.lock()->getDepth();
}

void IzBandCompressorControls::deriveDependentVariables()
{
    attack = compressorControls.lock()->getAttack();
    release = compressorControls.lock()->getRelease();
}

void IzBandCompressorControls::derive(ctoot::control::Control* c)
{
	auto id = c->getId();
	auto n = 0;
	auto cc = compressorControls;
	switch (id) {
	case DynamicsControlIds::THRESHOLD:
		threshold = cc.lock()->getThreshold();
		inverseThreshold = cc.lock()->getInverseThreshold();
	case DynamicsControlIds::RATIO:
		inverseRatio = cc.lock()->getInverseRatio();
		break;
	case DynamicsControlIds::ATTACK:
		attack = cc.lock()->getAttack();
		break;
	case DynamicsControlIds::HOLD:
		hold = cc.lock()->getHold();
		break;
	case DynamicsControlIds::RELEASE:
		release = cc.lock()->getRelease();
		break;
	case DynamicsControlIds::GAIN:
		gain = cc.lock()->getGain();
		break;
	case DynamicsControlIds::DEPTH:
		depth = cc.lock()->getDepth();
		break;
	}
}

void IzBandCompressorControls::update(float sampleRate)
{
    compressorControls.lock()->update(sampleRate);
    deriveDependentVariables();
}

float IzBandCompressorControls::getThreshold()
{
    return threshold;
}

float IzBandCompressorControls::getInverseThreshold()
{
    return inverseThreshold;
}

float IzBandCompressorControls::getKnee()
{
    return knee;
}

float IzBandCompressorControls::getInverseRatio()
{
    return inverseRatio;
}

float IzBandCompressorControls::getAttack()
{
    return attack;
}

float IzBandCompressorControls::getRelease()
{
    return release;
}

float IzBandCompressorControls::getGain()
{
    return gain;
}

float IzBandCompressorControls::getDepth()
{
    return depth;
}

void IzBandCompressorControls::setDynamicGain(float gain)
{
    compressorControls.lock()->setDynamicGain(gain);
}

bool IzBandCompressorControls::isBypassed()
{
    return AudioControls::isBypassed();
}
